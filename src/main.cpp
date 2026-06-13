/**
Autores: Juan Esteban Hoyos Ortiz - 2540054
Juan José Montaño Dosman - 2538124
Santiago Muñoz Bolaños - 2539226

 * @file main.cpp
 * @brief Punto de entrada principal del juego "Bus Escape: Traffic Jam C++ Edition"
 *
 * Implementa el bucle principal del juego siguiendo el patron MVC:
 * 1. Seleccion de nivel (1-3)
 * 2. Carga del modelo (MNivel) desde archivo
 * 3. Creacion del controlador (CJuego) y la vista (VDisplay)
 * 4. Bucle de juego: mostrar estado, verificar fin, recibir entrada, ejecutar movimiento
 *
 * @see MNivel, CJuego, VDisplay
 */

#include <iostream>
#include <string>
#include <cctype>
#include "MNivel.h"
#include "CJuego.h"
#include "VDisplay.h"

/**
 * @brief Punto de entrada del programa
 * @return 0 al terminar el juego
 *
 * Flujo principal:
 *
 * 1. SELECCION DE NIVEL: Solicita al usuario un numero del 1 al 3.
 *    Valida que este en rango (por defecto nivel 1).
 *
 * 2. CARGA DEL MODELO: Crea MNivel y llama a cargarArchivo() con la
 *    ruta del archivo de nivel correspondiente.
 *
 * 3. INICIALIZACION: Crea el controlador CJuego (con referencias a los
 *    vectores del modelo) y la vista VDisplay.
 *
 * 4. BUCLE PRINCIPAL:
 *    a. Mostrar tablero y estado actual via VDisplay::mostrarTablero()
 *    b. Verificar victoria (personas.empty()) - si true, salir
 *    c. Verificar derrota (todos parqueados + personas) - si true, salir
 *    d. Solicitar movimiento: indice del vehiculo, direccion (WASD), pasos
 *    e. Validar entrada del usuario (manejo de errores de cin)
 *    f. Convertir WASD a (dx, dy) y ejecutar CJuego::moverVehiculo()
 *    g. Repetir hasta victoria, derrota, o salida voluntaria (indice -1)
 */
int main() {
    std::cout << "=== BUS ESCAPE: TRAFFIC JAM C++ EDITION ===" << std::endl;
    std::cout << "Seleccione nivel (1-3): ";
    int nivelSel;
    std::cin >> nivelSel;
    if (nivelSel < 1 || nivelSel > 3) nivelSel = 1;

    std::string archivoNivel = "niveles/nivel" + std::to_string(nivelSel) + ".txt";

    MNivel modelo;
    modelo.cargarArchivo(archivoNivel);

    CJuego juego(modelo.getPersonas(), modelo.getVehiculos(),
                 modelo.getAncho(), modelo.getAlto());
    VDisplay vista(modelo.getAncho(), modelo.getAlto());

    bool juegoTerminado = false;
    while (!juegoTerminado) {
        int totalV = static_cast<int>(juego.getVehiculos().size());
        vista.mostrarTablero(juego.getVehiculos(), juego.getPersonas(),
                             juego.getPersonasAbordadas(),
                             juego.getVehiculosParqueados(), totalV);

        if (juego.verificarVictoria()) {
            std::cout << "FELICIDADES! Has recogido a todos los pasajeros!" << std::endl;
            break;
        }
        if (juego.verificarDerrota()) {
            std::cout << "GAME OVER! Los parqueos estan llenos." << std::endl;
            break;
        }

        std::cout << "--- MOVIMIENTO ---" << std::endl;
        std::cout << "Indice del vehiculo (-1 para salir): ";
        int idx;
        if (!(std::cin >> idx)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Entrada invalida!" << std::endl;
            continue;
        }
        if (idx < 0) break;

        std::cout << "Direccion (W=arriba, S=abajo, A=izquierda, D=derecha): ";
        char dir;
        if (!(std::cin >> dir)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Entrada invalida!" << std::endl;
            continue;
        }
        dir = std::toupper(dir);

        std::cout << "Pasos: ";
        int pasos;
        if (!(std::cin >> pasos)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Entrada invalida!" << std::endl;
            continue;
        }

        int dx = 0, dy = 0;
        switch (dir) {
            case 'W': dy = -1; break;
            case 'S': dy = 1;  break;
            case 'A': dx = -1; break;
            case 'D': dx = 1;  break;
            default:
                std::cerr << "Direccion invalida!" << std::endl;
                continue;
        }

        juego.moverVehiculo(idx, dx, dy, pasos);
    }

    return 0;
}
