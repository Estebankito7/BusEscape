#ifndef VEHICULO_H
#define VEHICULO_H

#include "Objeto.h"

/**
 * @class Vehiculo
 * @brief Representa un vehiculo (bus o carro) en el tablero del juego
 *
 * Hereda de Objeto y anade atributos de posicion, direccion y tamano.
 * Los vehiculos se mueven unicamente en el eje definido por su direccion:
 * - Horizontales (H): se desplazan en X (izquierda/derecha), Y fijo
 * - Verticales (V): se desplazan en Y (arriba/abajo), X fijo
 *
 * Cuando un vehiculo llega al borde derecho (H) o inferior (V)
 * entra en una zona de parqueo y ya no puede seguir avanzando.
 *
 * El arreglo posicion[2] almacena [x, y] como la esquina superior
 * izquierda del vehiculo. Las celdas que ocupa se calculan desde
 * ahi sumando el tamano en el eje de direccion.
 */
class Vehiculo : public Objeto {
private:
    int tamano;       /**< Longitud del vehiculo en casillas */
    int posicion[2];  /**< Posicion en el tablero: [x, y] (esquina superior izquierda) */
    int direccion[2]; /**< Direccion de movimiento: [dx, dy] (1,0)=H, (0,1)=V */

public:
    /**
     * @brief Constructor de Vehiculo
     * @param color Color del vehiculo (del enumerado colores)
     * @param tam Tamano del vehiculo en casillas (2 o 3)
     * @param x Posicion inicial en X (columna, 0 = izquierda)
     * @param y Posicion inicial en Y (fila, 0 = arriba)
     * @param ori Orientacion: 'H' para horizontal, 'V' para vertical
     *
     * La orientacion define el eje de movimiento:
     * - 'H': direccion[0]=1, direccion[1]=0 (se mueve en X)
     * - 'V': direccion[0]=0, direccion[1]=1 (se mueve en Y)
     */
    Vehiculo(colores color, int tam, int x, int y, char ori);

    /**
     * @brief Obtiene la posicion actual del vehiculo
     * @return Puntero a arreglo interno de 2 enteros [x, y]
     *
     * Devuelve referencia directa al arreglo interno. No copiar.
     * La posicion es la esquina superior izquierda del vehiculo.
     */
    const int* getPosicion() const;

    /**
     * @brief Obtiene la direccion del vehiculo
     * @return Puntero a arreglo interno de 2 enteros [dx, dy]
     *
     * (1,0) = horizontal, (0,1) = vertical.
     * Cada vehiculo solo se mueve en un eje.
     */
    const int* getDireccion() const;

    /**
     * @brief Obtiene el tamano del vehiculo
     * @return Numero de casillas que ocupa el vehiculo
     *
     * Ej: tamano=2 ocupa 2 casillas en el eje de direccion.
     */
    int getTamano() const;

    /**
     * @brief Establece la posicion del vehiculo
     * @param x Nueva coordenada X (columna)
     * @param y Nueva coordenada Y (fila)
     *
     * Solo el controlador (CJuego) llama a este metodo despues de
     * validar que el movimiento es legal.
     */
    void setPosicion(int x, int y);

    /**
     * @brief Verifica si el vehiculo puede moverse en una direccion dada
     * @param dx Componente X de la direccion deseada (-1, 0, 1)
     * @param dy Componente Y de la direccion deseada (-1, 0, 1)
     * @return true si el movimiento respeta la orientacion del vehiculo
     *
     * Reglas de validacion:
     * - No se permite movimiento diagonal (dx y dy distintos de 0)
     * - Vehiculo H solo acepta dx != 0 (izquierda/derecha)
     * - Vehiculo V solo acepta dy != 0 (arriba/abajo)
     */
    bool puedeMoverse(int dx, int dy) const;
};

#endif
