#include "Vehiculo.h"

/**
 * @brief Constructor de Vehiculo
 * @param color Color del vehiculo (rojo, verde, amarillo)
 * @param tam Numero de casillas que ocupa (2 o 3)
 * @param x Coordenada X inicial (columna, esquina superior izquierda)
 * @param y Coordenada Y inicial (fila, esquina superior izquierda)
 * @param ori Orientacion: 'H' horizontal (se mueve en X) o 'V' vertical (se mueve en Y)
 *
 * La orientacion determina el arreglo direccion[2]:
 * - 'H': [1, 0] — el vehiculo se desplaza horizontalmente
 * - 'V': [0, 1] — el vehiculo se desplaza verticalmente
 */
Vehiculo::Vehiculo(colores color, int tam, int x, int y, char ori)
    : Objeto(color), tamano(tam) {
    posicion[0] = x;
    posicion[1] = y;
    if (ori == 'H' || ori == 'h') {
        direccion[0] = 1;
        direccion[1] = 0;
    } else {
        direccion[0] = 0;
        direccion[1] = 1;
    }
}

/**
 * @brief Obtiene la posicion actual (esquina superior izquierda)
 * @return Puntero al arreglo interno [x, y]
 *
 * El valor retornado apunta a datos internos. No liberar ni asumir
 * que es valido despues de modificar el Vehiculo.
 */
const int* Vehiculo::getPosicion() const {
    return posicion;
}

/**
 * @brief Obtiene la direccion del vehiculo
 * @return Puntero al arreglo interno [dx, dy]
 *
 * (1, 0) = horizontal, (0, 1) = vertical.
 */
const int* Vehiculo::getDireccion() const {
    return direccion;
}

/**
 * @brief Obtiene el tamano del vehiculo
 * @return Cantidad de casillas que ocupa en su eje de movimiento
 */
int Vehiculo::getTamano() const {
    return tamano;
}

/**
 * @brief Actualiza la posicion del vehiculo
 * @param x Nueva coordenada X
 * @param y Nueva coordenada Y
 *
 * El controlador llama a este metodo despues de validar que
 * el movimiento es legal (sin colisiones, dentro del tablero).
 */
void Vehiculo::setPosicion(int x, int y) {
    posicion[0] = x;
    posicion[1] = y;
}

/**
 * @brief Verifica si la direccion solicitada es compatible con el vehiculo
 * @param dx Componente X deseada (-1, 0, 1)
 * @param dy Componente Y deseada (-1, 0, 1)
 * @return true si el vehiculo puede moverse en esa direccion
 *
 * Logica de validacion:
 * - Rechaza diagonal: dx y dy distintos de 0 simultaneamente
 * - H(1,0): solo acepta dx != 0 (izquierda o derecha)
 * - V(0,1): solo acepta dy != 0 (arriba o abajo)
 *
 * Ejemplo: Vehiculo H con puedeMoverse(0, 1) retorna false.
 */
bool Vehiculo::puedeMoverse(int dx, int dy) const {
    if (dx != 0 && dy != 0) return false;
    if (direccion[0] != 0 && dx == 0) return false;
    if (direccion[1] != 0 && dy == 0) return false;
    return true;
}
