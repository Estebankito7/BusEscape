#ifndef PERSONA_H
#define PERSONA_H

#include "Objeto.h"

/**
 * @class Persona
 * @brief Representa un pasajero que espera ser recogido por un vehiculo
 *
 * Hereda de Objeto. Su color determina con que vehiculo puede abordar
 * (coincidencia de color evaluada polimorficamente por el controlador).
 *
 * Cada pasajero tiene una posicion fija [x, y] en el tablero definida
 * en el archivo de nivel. Cuando un vehiculo pasa sobre esa posicion
 * durante su movimiento, el pasajero se sube (se elimina del vector).
 *
 * Los pasajeros NO se muestran dentro del grid del tablero en consola,
 * solo aparecen en la seccion "PASAJEROS" del informe textual.
 *
 * Restriccion: El color AZUL (3) nunca se asigna a pasajeros porque
 * no existe un vehiculo de ese color que pueda recogerlos.
 *
 * @see CJuego::verificarAbordaje
 * @see CJuego::validarColor
 */
class Persona : public Objeto {
private:
    int posicion[2]; /**< Posicion en el tablero: [x, y] */

public:
    /**
     * @brief Constructor de Persona
     * @param c Color de la persona (rojo=0, verde=1, amarillo=2)
     * @param x Posicion X en el tablero (columna, 0 = izquierda)
     * @param y Posicion Y en el tablero (fila, 0 = arriba)
     *
     * La posicion define las coordenadas exactas donde el pasajero
     * espera. Cuando un vehiculo se mueve, el controlador verifica
     * si alguna celda barrida coincide con esta posicion.
     */
    Persona(colores c, int x, int y);

    /**
     * @brief Obtiene la posicion X
     * @return Coordenada X (columna) en el tablero
     */
    int getX() const;

    /**
     * @brief Obtiene la posicion Y
     * @return Coordenada Y (fila) en el tablero
     */
    int getY() const;
};

#endif
