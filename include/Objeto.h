#ifndef OBJETO_H
#define OBJETO_H

/**
 * @file Objeto.h
 * @brief Definicion de la clase base Objeto y el enumerado colores
 */

/**
 * @enum colores
 * @brief Colores disponibles para vehiculos y personas en el juego
 *
 * Cada vehiculo y pasajero tiene un color. Un pasajero solo puede abordar
 *
 */
enum colores { rojo, verde, amarillo };

/**
 * @class Objeto
 * @brief Clase base que representa un elemento del juego con un color
 *
 * Clase base del modelo para el patron MVC. Implementa el atributo
 * color que heredan Vehiculo y Persona. Permite polimorfismo:
 * el controlador valida coincidencias de color usando referencias
 * a Objeto sin conocer el tipo derivado.
 *
 * @see Vehiculo
 * @see Persona
 */
class Objeto {
private:
    colores color; /**< Color del objeto */

public:
    /**
     * @brief Constructor por defecto
     * @param c Color del objeto (por defecto rojo)
     */
    Objeto(colores c = rojo);

    /**
     * @brief Obtiene el color del objeto
     * @return Color actual del objeto
     */
    colores getColor() const;

    /**
     * @brief Establece el color del objeto
     * @param c Nuevo color para el objeto
     */
    void setColor(colores c);
};

#endif
