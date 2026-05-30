#ifndef Cjuego_H
#define Cjuego_H

#include <vector>
#include "Vehiculo.h"
#include "Persona.h"
#include "Objeto.h"

/**
 * @class CJuego
 * @brief Controlador principal del juego (capa controlador del patrón MVC)
 *
 * Gestiona toda la logica del juego:
 * - Movimiento de vehiculos con deteccion de colisiones
 * - Validacion de colores para abordaje de pasajeros (polimorfica)
 * - Parqueo de vehiculos en bordes del tablero
 * - Condiciones de victoria/derrota
 *
 * Opera sobre los vectores del modelo (MNivel) por referencia y se comunica
 * con la vista (VDisplay) para mostrar el estado actual.
 *
 * @see MNivel (modelo)
 * @see VDisplay (vista)
 */
class CJuego {
private:
    Vehiculo* parqueo[10];            /**< Zonas de parqueo (max 10 vehiculos) */
    std::vector<Persona>& personas;   /**< Referencia a las personas del modelo */
    std::vector<Vehiculo>& vehiculos; /**< Referencia a los vehiculos del modelo */
    int ancho;                        /**< Ancho del tablero en casillas */
    int alto;                         /**< Alto del tablero en casillas */
    int personasAbordadas;            /**< Contador de personas que abordaron */
    int vehiculosParqueados;          /**< Contador de vehiculos parqueados */

    /**
     * @brief Valida si el color de una persona coincide con el de un vehiculo
     * @param persona Referencia a la persona (como Objeto)
     * @param vehiculo Referencia al vehiculo (como Objeto)
     *
     * Metodo polimorfico: recibe referencias a la clase base Objeto
     * pero en tiempo de ejecucion son Persona y Vehiculo. Compara
     * colores y si coinciden, incrementa el contador personasAbordadas.
     *
     * El polimorfismo aqui permite que el mismo metodo sirva para
     * cualquier combinacion de tipos derivados de Objeto.
     */
    void validarColor(Objeto& persona, Objeto& vehiculo);

    /**
     * @brief Verifica si hay personas en la trayectoria del vehiculo
     * @param vehiculo El vehiculo que se movio (referencia modificable)
     * @param oldX Posicion X anterior del vehiculo (antes del movimiento)
     * @param oldY Posicion Y anterior del vehiculo (antes del movimiento)
     *
     * Barre TODA la trayectoria desde la posicion anterior hasta la nueva,
     * no solo la posicion final. Para vehiculos horizontales barre en X,
     * para verticales barre en Y. Si encuentra una persona en alguna celda
     * barrida y el color coincide, la elimina del vector de personas.
     */
    void verificarAbordaje(Vehiculo& vehiculo, int oldX, int oldY);

public:
    /**
     * @brief Constructor de CJuego
     * @param p Referencia al vector de personas del modelo (MNivel)
     * @param v Referencia al vector de vehiculos del modelo (MNivel)
     * @param w Ancho del tablero en casillas
     * @param h Alto del tablero en casillas
     *
     * Inicializa todos los punteros de parqueo a nullptr y los
     * contadores a 0. Las referencias a los vectores permiten
     * modificar directamente el modelo sin copias.
     */
    CJuego(std::vector<Persona>& p, std::vector<Vehiculo>& v, int w, int h);

    /**
     * @brief Mueve un vehiculo en una direccion y verifica consecuencias
     * @param indice Indice del vehiculo en el vector vehiculos
     * @param dx Componente X de la direccion (-1, 0, 1)
     * @param dy Componente Y de la direccion (-1, 0, 1)
     * @param pasos Numero de casillas a moverse (>= 1)
     * @return true si el movimiento fue exitoso
     *
     * Proceso completo del movimiento:
     * 1. Valida que el indice sea valido
     * 2. Verifica que la direccion sea compatible con la orientacion del vehiculo
     * 3. Calcula la nueva posicion y verifica limites del tablero
     * 4. Verifica colision con otros vehiculos en toda la trayectoria
     *    (cada paso intermedio, cada celda del vehiculo)
     * 5. Si todo es valido: actualiza posicion, verifica abordaje de
     *    pasajeros en la trayectoria barrida, y verifica si parquea
     */
    bool moverVehiculo(int indice, int dx, int dy, int pasos);

    /**
     * @brief Verifica si un vehiculo debe marcarce como parqueado
     * @param vehiculo El vehiculo a verificar
     *
     * Condicion de parqueo segun orientacion:
     * - H: borde derecho alcanzado (x + tamano >= ancho)
     * - V: borde inferior alcanzado (y + tamano >= alto)
     *
     * Si cumple la condicion y aun hay espacio en el arreglo parqueo[10],
     * almacena el puntero al vehiculo e incrementa el contador.
     * El maximo de parqueos es min(vehiculos.size(), 10).
     */
    void verificarParqueo(Vehiculo& vehiculo);

    /**
     * @brief Verifica si el jugador ha ganado la partida
     * @return true si no quedan personas pendientes en el vector
     *
     * Victoria = todos los pasajeros fueron recogidos.
     * Se verifica despues de cada movimiento exitoso.
     */
    bool verificarVictoria() const;

    /**
     * @brief Verifica si el jugador ha perdido la partida
     * @return true si todos los vehiculos estan parqueados y hay pasajeros
     *
     * Derrota = todos los vehiculos ocuparon los parqueos pero
     * aun quedan personas esperando (no pudieron ser recogidas).
     * Se verifica despues de cada movimiento exitoso.
     */
    bool verificarDerrota() const;

    /**
     * @brief Obtiene el numero de personas abordadas
     * @return Cantidad de personas que ya abordaron (contador)
     */
    int getPersonasAbordadas() const;

    /**
     * @brief Obtiene el numero de vehiculos parqueados
     * @return Cantidad de vehiculos ya parqueados
     */
    int getVehiculosParqueados() const;

    /**
     * @brief Obtiene las personas restantes (no abordadas)
     * @return Referencia al vector de personas del modelo
     */
    std::vector<Persona>& getPersonas();

    /**
     * @brief Obtiene los vehiculos del juego
     * @return Referencia al vector de vehiculos del modelo
     */
    std::vector<Vehiculo>& getVehiculos();
};

#endif
