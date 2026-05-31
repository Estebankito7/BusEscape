#include "VDisplay.h"
#include <iostream>
#include <iomanip>

/**
 * @brief Constructor de la vista VDisplay
 * @param w Ancho del tablero en casillas
 * @param h Alto del tablero en casillas
 */
VDisplay::VDisplay(int w, int h) : ancho(w), alto(h) {}

/**
 * @brief Convierte el enumerado colores a su nombre en espanol
 * @param c Color del enumerado colores
 * @return Cadena con el nombre: "ROJO", "VERDE", "AMARILLO" o "DESC"
 */
const char* VDisplay::colorToString(colores c) const {
    switch (c) {
        case rojo:    return "ROJO";
        case verde:   return "VERDE";
        case amarillo:return "AMARILLO";
        default:      return "DESC";
    }
}

/**
 * @brief Renderiza el estado completo del juego en consola
 * @param vehiculos Vector de vehiculos a dibujar en el grid
 * @param personas Vector de personas esperando (NO se dibujan en el grid)
 * @param abordadas Cantidad de personas que ya abordaron
 * @param parqueados Cantidad de vehiculos en zona de parqueo
 * @param totalVehiculos Cantidad total de vehiculos en el nivel
 *
 * Proceso de renderizado:
 *
 * 1. ENCABEZADO: Muestra nombre del juego, dimensiones del tablero,
 *    contador de personas abordadas y vehiculos parqueados/total.
 *
 * 2. GRID DEL TABLERO:
 *    a. Inicializa todo el grid con '.' (celda vacia)
 *    b. Para cada vehiculo, dibuja sus celdas:
 *       - Primera celda (t=0): digito del indice del vehiculo ('0'-'9')
 *       - Celdas restantes: '-' si es H, '|' si es V
 *    c. Las personas NO se dibujan en el grid (solo en la lista textual)
 *    d. Imprime numeros de columna (0..ancho-1) y fila (0..alto-1)
 *
 * 3. LISTA DE VEHICULOS: Indice, color, posicion (x,y), tamano y
 *    orientacion (H o V) para cada vehiculo.
 *
 * 4. LISTA DE PASAJEROS: Indice y color de cada persona esperando,
 *    o mensaje "No hay pasajeros esperando!" si ya abordaron todos.
 */
void VDisplay::mostrarTablero(const std::vector<Vehiculo>& vehiculos,
                              const std::vector<Persona>& personas,
                              int abordadas,
                              int parqueados,
                              int totalVehiculos) const {
    std::cout << "\n========== BUS ESCAPE ==========" << std::endl;
    std::cout << "Tablero: " << ancho << "x" << alto << std::endl;
    std::cout << "Personas abordadas: " << abordadas
              << " | Parqueados: " << parqueados << "/" << totalVehiculos << std::endl;
    std::cout << std::endl;

    // Inicializar grid con celdas vacias
    char grid[alto][ancho];
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            grid[y][x] = '.';
        }
    }

    // Dibujar vehiculos en el grid
    for (size_t i = 0; i < vehiculos.size(); i++) {
        const int* pos = vehiculos[i].getPosicion();
        const int* dir = vehiculos[i].getDireccion();
        int tam = vehiculos[i].getTamano();

        char id = '0' + static_cast<char>(i);
        if (id > '9') id = '*';

        for (int t = 0; t < tam; t++) {
            int x = pos[0] + (dir[0] != 0 ? t : 0);
            int y = pos[1] + (dir[1] != 0 ? t : 0);
            if (x >= 0 && x < ancho && y >= 0 && y < alto) {
                grid[y][x] = (t == 0) ? id : (dir[0] != 0 ? '-' : '|');
            }
        }
    }

    // Encabezado de columnas
    std::cout << "   ";
    for (int x = 0; x < ancho; x++) {
        std::cout << " " << x;
    }
    std::cout << std::endl;

    // Borde superior del grid
    std::cout << "   +";
    for (int x = 0; x < ancho; x++) {
        std::cout << "--";
    }
    std::cout << "+" << std::endl;

    // Filas del grid con numero de fila al inicio
    for (int y = 0; y < alto; y++) {
        std::cout << y << "  |";
        for (int x = 0; x < ancho; x++) {
            std::cout << " " << grid[y][x];
        }
        std::cout << " |" << std::endl;
    }

    // Borde inferior del grid
    std::cout << "   +";
    for (int x = 0; x < ancho; x++) {
        std::cout << "--";
    }
    std::cout << "+" << std::endl;

    std::cout << std::endl;
    // Lista de vehiculos con sus atributos
    std::cout << "--- VEHICULOS ---" << std::endl;
    for (size_t i = 0; i < vehiculos.size(); i++) {
        const int* pos = vehiculos[i].getPosicion();
        colores c = vehiculos[i].getColor();
        int tam = vehiculos[i].getTamano();
        std::cout << "  " << i << ": " << colorToString(c)
                  << " (" << pos[0] << "," << pos[1] << ")"
                  << " T:" << tam;
        if (vehiculos[i].getDireccion()[0] != 0) {
            std::cout << " H";
        } else {
            std::cout << " V";
        }
        std::cout << std::endl;
    }

    // Lista de pasajeros esperando
    std::cout << "--- PASAJEROS ---" << std::endl;
    if (personas.empty()) {
        std::cout << "  No hay pasajeros esperando!" << std::endl;
    } else {
        for (size_t i = 0; i < personas.size(); i++) {
            std::cout << "  " << i << ": " << colorToString(personas[i].getColor()) << std::endl;
        }
    }
    std::cout << std::endl;
}
