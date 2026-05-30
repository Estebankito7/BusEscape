#ifndef VDISPLAY_H
#define VDISPLAY_H

#include <vector>
#include "Vehiculo.h"
#include "Persona.h"

/**
 * @class VDisplay
 * @brief Vista encargada de la representacion visual del juego en consola
 *        (capa vista del patrón MVC)
 *
 * Dibuja el tablero con los vehiculos identificados por numero y color,
 * muestra las personas esperando y el estado de las zonas de parqueo.
 *
 * La representacion es puramente textual (ASCII):
 * - Vehiculo H: usa '-' para las extensiones
 * - Vehiculo V: usa '|' para las extensiones
 * - Primera celda de cada vehiculo: su indice numerico (0-9)
 * - Celdas vacias: '.'
 *
 * Los pasajeros NO se muestran dentro del grid, solo en la lista
 * de "PASAJEROS" debajo del tablero.
 */
class VDisplay {
private:
    int ancho; /**< Ancho del tablero a mostrar */
    int alto;  /**< Alto del tablero a mostrar */

    /**
     * @brief Convierte un color del enumerado a su nombre en texto
     * @param c Color del enumerado colores (rojo, verde, amarillo, azul)
     * @return Cadena con el nombre del color en espanol
     *
     * Usada internamente por mostrarTablero() para la lista de vehiculos.
     * Para colores desconocidos retorna "DESC".
     */
    const char* colorToString(colores c) const;

public:
    /**
     * @brief Constructor de VDisplay
     * @param w Ancho del tablero en casillas
     * @param h Alto del tablero en casillas
     */
    VDisplay(int w, int h);

    /**
     * @brief Muestra el tablero completo y estado del juego en consola
     * @param vehiculos Vector de vehiculos a dibujar
     * @param personas Vector de personas esperando
     * @param abordadas Cantidad de personas que ya abordaron
     * @param parqueados Cantidad de vehiculos parqueados actualmente
     * @param totalVehiculos Cantidad total de vehiculos en el nivel
     *
     * Renderiza en este orden:
     * 1. Encabezado con dimensiones y contadores (abordados/parqueados)
     * 2. Grid del tablero con cada vehiculo dibujado celda por celda
     * 3. Lista de vehiculos con indice, color, posicion, tamano y orientacion
     * 4. Lista de pasajeros esperando (o mensaje "No hay pasajeros")
     *
     * Los vehiculos se renderizan con su indice en la primera celda y
     * caracteres '-' (H) o '|' (V) en las celdas restantes.
     */
    void mostrarTablero(const std::vector<Vehiculo>& vehiculos,
                        const std::vector<Persona>& personas,
                        int abordadas,
                        int parqueados,
                        int totalVehiculos) const;
};

#endif
