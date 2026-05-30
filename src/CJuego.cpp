#include "CJuego.h"
#include <iostream>
#include <algorithm>

/**
 * @brief Constructor del controlador CJuego
 * @param p Referencia al vector de personas del modelo
 * @param v Referencia al vector de vehiculos del modelo
 * @param w Ancho del tablero en casillas
 * @param h Alto del tablero en casillas
 *
 * Inicializa todas las referencias y contadores.
 * El arreglo parqueo[10] se inicializa con nullptr en todas sus posiciones.
 * Los contadores personasAbordadas y vehiculosParqueados comienzan en 0.
 */
CJuego::CJuego(std::vector<Persona>& p, std::vector<Vehiculo>& v, int w, int h)
    : personas(p), vehiculos(v), ancho(w), alto(h),
      personasAbordadas(0), vehiculosParqueados(0) {
    for (int i = 0; i < 10; i++) {
        parqueo[i] = nullptr;
    }
}

/**
 * @brief Valida polimorficamente si el color de una persona coincide con un vehiculo
 * @param persona Referencia a Objeto que en runtime es una Persona
 * @param vehiculo Referencia a Objeto que en runtime es un Vehiculo
 *
 * Metodo polimorfico: ambos parametros se pasan como Objeto& pero en
 * tiempo de ejecucion son tipos derivados (Persona y Vehiculo).
 * Si los colores coinciden, incrementa el contador de personas abordadas.
 */
void CJuego::validarColor(Objeto& persona, Objeto& vehiculo) {
    if (persona.getColor() == vehiculo.getColor()) {
        std::cout << "Color coincide! Persona aborda el vehiculo." << std::endl;
        personasAbordadas++;
    }
}

/**
 * @brief Mueve un vehiculo validando colisiones y limites
 * @param indice Indice del vehiculo en el vector vehiculos
 * @param dx Direccion en X (-1=izquierda, 0, 1=derecha)
 * @param dy Direccion en Y (-1=arriba, 0, 1=abajo)
 * @param pasos Numero de casillas a desplazar
 * @return true si el movimiento se ejecuto exitosamente
 *
 * Proceso detallado de validacion:
 *
 * 1. VALIDACION BASICA: Verifica que el indice este en rango
 *    y que la direccion sea compatible con la orientacion del vehiculo
 *    (un vehiculo H no puede moverse arriba/abajo).
 *
 * 2. LIMITES DEL TABLERO: Calcula la posicion destino y verifica
 *    que todas las celdas que ocuparia el vehiculo queden dentro del tablero.
 *    Para vehiculos H: x + tam <= ancho. Para V: y + tam <= alto.
 *
 * 3. COLISION: Para cada paso intermedio y para cada celda del vehiculo,
 *    verifica si alguna celda coincide con las celdas de OTROS vehiculos.
 *    Usa tres bucles anidados: pasos (1..N) x celdas del vehiculo
 *    (0..tam-1) x celdas de cada otro vehiculo (0..t2-1).
 *
 *    Nota: cada vehiculo calcula sus celdas usando su propia direccion
 *    (dirV para el que se mueve, dir2 para los otros), evitando falsos
 *    positivos entre vehiculos de orientacion perpendicular.
 *
 * 4. EJECUCION: Si todas las validaciones pasan:
 *    - Guarda la posicion anterior (oldX, oldY)
 *    - Actualiza la posicion del vehiculo
 *    - Llama a verificarAbordaje() para recoger pasajeros en la trayectoria
 *    - Llama a verificarParqueo() para ver si llego al borde
 */
bool CJuego::moverVehiculo(int indice, int dx, int dy, int pasos) {
    if (indice < 0 || indice >= static_cast<int>(vehiculos.size())) {
        std::cerr << "Error: Indice de vehiculo invalido." << std::endl;
        return false;
    }

    Vehiculo& v = vehiculos[indice];

    if (!v.puedeMoverse(dx, dy)) {
        std::cerr << "Error: El vehiculo no puede moverse en esa direccion." << std::endl;
        return false;
    }

    const int* pos = v.getPosicion();
    const int* dirV = v.getDireccion();
    int tamV = v.getTamano();
    int nuevaX = pos[0] + dx * pasos;
    int nuevaY = pos[1] + dy * pasos;

    // Verificar que el vehiculo completo quepa dentro del tablero
    // Para H: nuevaX + tamV debe estar dentro del ancho
    // Para V: nuevaY + tamV debe estar dentro del alto
    if (nuevaX < 0 || nuevaX + (dirV[0] != 0 ? tamV : 1) > ancho ||
        nuevaY < 0 || nuevaY + (dirV[1] != 0 ? tamV : 1) > alto) {
        std::cerr << "Error: Movimiento fuera del tablero." << std::endl;
        return false;
    }

    // Verificar colisiones con otros vehiculos
    bool caminoLibre = true;
    for (size_t i = 0; i < vehiculos.size(); i++) {
        if (static_cast<int>(i) == indice) continue; // no colisiona consigo mismo
        const Vehiculo& otro = vehiculos[i];
        const int* pos2 = otro.getPosicion();
        const int* dir2 = otro.getDireccion();
        int t2 = otro.getTamano();

        // Para cada paso intermedio del movimiento
        for (int paso = 1; paso <= pasos; paso++) {
            // Para cada celda del vehiculo que se mueve
            for (int t = 0; t < tamV; t++) {
                // Celda del vehiculo movil en este paso intermedio
                int cx = pos[0] + dx * paso + (dirV[0] != 0 ? t : 0);
                int cy = pos[1] + dy * paso + (dirV[1] != 0 ? t : 0);

                // Para cada celda del otro vehiculo (posicion actual)
                for (int ot = 0; ot < t2; ot++) {
                    int ox = pos2[0] + (dir2[0] != 0 ? ot : 0);
                    int oy = pos2[1] + (dir2[1] != 0 ? ot : 0);

                    if (cx == ox && cy == oy) {
                        caminoLibre = false;
                        goto finVerificacion;
                    }
                }
            }
        }
    }

finVerificacion:
    if (!caminoLibre) {
        std::cerr << "Error: Camino bloqueado por otro vehiculo." << std::endl;
        return false;
    }

    // Movimiento valido: ejecutar
    int oldX = pos[0];
    int oldY = pos[1];
    v.setPosicion(nuevaX, nuevaY);
    std::cout << "Vehiculo " << indice << " movido a (" << nuevaX << ", " << nuevaY << ")"
              << std::endl;

    verificarAbordaje(v, oldX, oldY);
    verificarParqueo(v);

    return true;
}

/**
 * @brief Verifica si hay pasajeros en la trayectoria barrida por el vehiculo
 * @param vehiculo Referencia al vehiculo que se movio
 * @param oldX Posicion X antes del movimiento
 * @param oldY Posicion Y antes del movimiento
 *
 * Algoritmo de barrido trayectoria completa:
 *
 * En lugar de solo verificar la posicion final, este metodo barre TODAS
 * las celdas entre la posicion anterior y la nueva posicion, incluyendo
 * el tamano completo del vehiculo. Esto asegura que pasajeros en medio
 * del camino sean detectados.
 *
 * Para vehiculos HORIZONTALES (dirV[0] != 0):
 *   - Barre en X desde min(oldX, newX) hasta max(oldX, newX) + tam - 1
 *   - Y fijo = posV[1]
 *   - Verifica si (x, Y) coincide con (px, py) de alguna persona
 *
 * Para vehiculos VERTICALES (dirV[1] != 0):
 *   - Barre en Y desde min(oldY, newY) hasta max(oldY, newY) + tam - 1
 *   - X fijo = posV[0]
 *   - Verifica si (X, y) coincide con (px, py) de alguna persona
 *
 * Por cada coincidencia de posicion:
 * 1. Llama a validarColor() para verificar que el color coincida
 * 2. Si el color coincide, marca la persona para eliminar
 * 3. Las personas marcadas se eliminan del vector con erase()
 *
 * Esto permite que un vehiculo recoja MULTIPLES pasajeros en un solo
 * movimiento si pasan por varias posiciones.
 */
void CJuego::verificarAbordaje(Vehiculo& vehiculo, int oldX, int oldY) {
    const int* posV = vehiculo.getPosicion();
    int tamV = vehiculo.getTamano();
    const int* dirV = vehiculo.getDireccion();

    auto it = personas.begin();
    while (it != personas.end()) {
        int px = it->getX();
        int py = it->getY();
        bool aborda = false;

        // Vehiculo horizontal: barrer en X, Y fijo
        if (dirV[0] != 0) {
            for (int x = std::min(oldX, posV[0]); x < std::max(oldX, posV[0]) + tamV; x++) {
                if (x == px && posV[1] == py) {
                    Objeto& refPersona = *it;
                    Objeto& refVehiculo = vehiculo;
                    validarColor(refPersona, refVehiculo);
                    if (refPersona.getColor() == refVehiculo.getColor()) {
                        aborda = true;
                    }
                    break;
                }
            }
        }
        // Vehiculo vertical: barrer en Y, X fijo
        else {
            for (int y = std::min(oldY, posV[1]); y < std::max(oldY, posV[1]) + tamV; y++) {
                if (posV[0] == px && y == py) {
                    Objeto& refPersona = *it;
                    Objeto& refVehiculo = vehiculo;
                    validarColor(refPersona, refVehiculo);
                    if (refPersona.getColor() == refVehiculo.getColor()) {
                        aborda = true;
                    }
                    break;
                }
            }
        }

        if (aborda) {
            it = personas.erase(it); // erase() devuelve el siguiente iterador
        } else {
            ++it;
        }
    }
}

/**
 * @brief Verifica si un vehiculo debe marcarce como parqueado
 * @param vehiculo Referencia al vehiculo a verificar
 *
 * Condiciones de parqueo (segun orientacion):
 *
 * VEHICULO HORIZONTAL:
 *   Parquea cuando su extremo derecho alcanza el borde del tablero:
 *   posicion[0] + tamano >= ancho
 *   Ej: H en (8,0) con tam=2 → 8+2=10 >= 10 → PARQUEADO
 *
 * VEHICULO VERTICAL:
 *   Parquea cuando su extremo inferior alcanza el borde del tablero:
 *   posicion[1] + tamano >= alto
 *   Ej: V en (0,8) con tam=2 → 8+2=10 >= 10 → PARQUEADO
 *
 * Solo se parquea si aun hay espacio en el arreglo parqueo[10].
 * El maximo de parqueos es min(total_vehiculos, 10).
 */
void CJuego::verificarParqueo(Vehiculo& vehiculo) {
    const int* pos = vehiculo.getPosicion();
    const int* dir = vehiculo.getDireccion();
    int tam = vehiculo.getTamano();

    bool enBordeSalida = false;
    if (dir[0] != 0) {
        enBordeSalida = (pos[0] + tam >= ancho);
    } else {
        enBordeSalida = (pos[1] + tam >= alto);
    }

    int maxParqueo = std::min(static_cast<int>(vehiculos.size()), 10);
    if (enBordeSalida && vehiculosParqueados < maxParqueo) {
        parqueo[vehiculosParqueados] = &vehiculo;
        vehiculosParqueados++;
        std::cout << "Vehiculo parqueado en zona " << (vehiculosParqueados - 1) << std::endl;
    }
}

/**
 * @brief Verifica condicion de victoria
 * @return true si no quedan personas esperando
 *
 * Victoria = todos los pasajeros fueron recogidos.
 * Se evalua despues de cada movimiento exitoso en el main loop.
 */
bool CJuego::verificarVictoria() const {
    return personas.empty();
}

/**
 * @brief Verifica condicion de derrota
 * @return true si todos los vehiculos estan parqueados y hay pasajeros
 *
 * Derrota = todos los vehiculos ocuparon los parqueos pero aun
 * hay pasajeros que no pudieron ser recogidos (no habia vehiculo
 * del color correcto disponible o no se logro la coincidencia).
 *
 * Se evalua despues de cada movimiento exitoso en el main loop.
 */
bool CJuego::verificarDerrota() const {
    return vehiculosParqueados >= static_cast<int>(vehiculos.size()) && !personas.empty();
}

/**
 * @brief Obtiene cuantas personas han abordado vehiculos
 * @return Contador de personas abordadas
 */
int CJuego::getPersonasAbordadas() const {
    return personasAbordadas;
}

/**
 * @brief Obtiene cuantos vehiculos estan parqueados
 * @return Contador de vehiculos en zona de parqueo
 */
int CJuego::getVehiculosParqueados() const {
    return vehiculosParqueados;
}

/**
 * @brief Obtiene referencia al vector de personas restantes
 * @return Referencia al vector de personas del modelo
 */
std::vector<Persona>& CJuego::getPersonas() {
    return personas;
}

/**
 * @brief Obtiene referencia al vector de vehiculos
 * @return Referencia al vector de vehiculos del modelo
 */
std::vector<Vehiculo>& CJuego::getVehiculos() {
    return vehiculos;
}
