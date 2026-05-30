#ifndef MNIVEL_H
#define MNIVEL_H

#include <vector>
#include <string>
#include "Persona.h"
#include "Vehiculo.h"

/**
 * @class MNivel
 * @brief Modelo que representa un nivel del juego (capa modelo del patrón MVC)
 *
 * Se encarga de cargar la configuracion del nivel desde un archivo .txt
 * y almacena los vectores de personas y vehiculos que componen el nivel.
 * El controlador (CJuego) recibe referencias a estos vectores para operar.
 *
 * Los metodos getPersonas() y getVehiculos() devuelven referencias
 * para que el controlador pueda modificar los datos directamente.
 */
class MNivel {
private:
    std::vector<Persona> personas;   /**< Lista de pasajeros del nivel */
    std::vector<Vehiculo> vehiculos; /**< Lista de vehiculos del nivel */
    int ancho;                       /**< Ancho del tablero en casillas */
    int alto;                        /**< Alto del tablero en casillas */

public:
    /**
     * @brief Constructor de MNivel
     *
     * Inicializa ancho y alto en 0. Los valores reales se cargan
     * al llamar a cargarArchivo().
     */
    MNivel();

    /**
     * @brief Carga la configuracion del nivel desde un archivo
     * @param nombreArchivo Ruta al archivo .txt de nivel
     *
     * Formato del archivo de nivel:
     * - Linea "# DIMENSIONES": siguiente linea tiene "ancho alto"
     * - Linea "# VEHICULOS": lineas siguientes con "Tipo Color X Y Orientacion Tamano"
     * - Linea "# PASAJEROS": lineas siguientes con "Color X Y"
     *
     * Ejemplo de vehiculo: "B 0 0 0 H 2" = Bus ROJO en (0,0) Horizontal tamano 2
     * Ejemplo de pasajero: "1 3 5" = Persona VERDE en posicion (3,5)
     *
     * Las lineas que comienzan con '#' son encabezados de seccion.
     * Las lineas vacias se ignoran.
     *
     * @see parser secuencial: lee linea por linea, cambia de modo al
     * encontrar encabezados (# DIMENSIONES, # VEHICULOS, # PASAJEROS)
     */
    void cargarArchivo(const std::string& nombreArchivo);

    /**
     * @brief Obtiene la lista de personas del nivel
     * @return Referencia al vector de personas (modificable)
     *
     * Devuelve referencia para que CJuego pueda modificar
     * (eliminar pasajeros que abordan).
     */
    std::vector<Persona>& getPersonas();

    /**
     * @brief Obtiene la lista de vehiculos del nivel
     * @return Referencia al vector de vehiculos (modificable)
     *
     * Devuelve referencia para que CJuego pueda modificar
     * (mover vehiculos).
     */
    std::vector<Vehiculo>& getVehiculos();

    /**
     * @brief Obtiene el ancho del tablero
     * @return Ancho en casillas (6, 8 o 10 segun nivel)
     */
    int getAncho() const;

    /**
     * @brief Obtiene el alto del tablero
     * @return Alto en casillas (6, 8 o 10 segun nivel)
     */
    int getAlto() const;
};

#endif
