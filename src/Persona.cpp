#include "Persona.h"

/**
 * @brief Constructor de Persona (pasajero)
 * @param c Color de la persona (determina con que vehiculo aborda)
 * @param x Coordenada X en el tablero donde espera
 * @param y Coordenada Y en el tablero donde espera
 *
 * La posicion es fija durante toda la partida. Si la persona
 * no es recogida, permanece en esa posicion.
 */
Persona::Persona(colores c, int x, int y) : Objeto(c) {
    posicion[0] = x;
    posicion[1] = y;
}

/**
 * @brief Obtiene la coordenada X del pasajero en el tablero
 * @return Columna donde se encuentra el pasajero
 */
int Persona::getX() const {
    return posicion[0];
}

/**
 * @brief Obtiene la coordenada Y del pasajero en el tablero
 * @return Fila donde se encuentra el pasajero
 */
int Persona::getY() const {
    return posicion[1];
}
