#include "Objeto.h"

/**
 * @brief Constructor de la clase base Objeto
 * @param c Color inicial del objeto (por defecto rojo)
 *
 * Inicializa el atributo color que heredaran Vehiculo y Persona.
 */
Objeto::Objeto(colores c) : color(c) {}

/**
 * @brief Obtiene el color del objeto
 * @return Color actual del tipo colores
 */
colores Objeto::getColor() const {
    return color;
}

/**
 * @brief Establece el color del objeto
 * @param c Nuevo color a asignar
 *
 * Permite cambiar el color en tiempo de ejecucion si es necesario.
 */
void Objeto::setColor(colores c) {
    color = c;
}
