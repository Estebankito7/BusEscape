#include "MNivel.h"
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief Constructor de MNivel
 *
 * Inicializa ancho y alto en 0. Los valores se cargaran
 * al llamar a cargarArchivo().
 */
MNivel::MNivel() : ancho(0), alto(0) {}

/**
 * @brief Carga y parsea un archivo de nivel completo
 * @param nombreArchivo Ruta al archivo .txt de nivel
 *
 * Parseador secuencial linea por linea con maquina de estado simple
 * basada en encabezados identificados por '#'. El flujo es:
 *
 * 1. Busca "# DIMENSIONES", lee la siguiente linea como "ancho alto"
 * 2. Busca "# VEHICULOS", lee lineas siguientes hasta encontrar otro '#'
 *    Cada linea: Tipo[1char] Color[int] X Y Orientacion[H|V] Tamano[int]
 *    Ej: "B 0 0 0 H 2" → Bus ROJO, pos (0,0), Horizontal, tam 2
 * 3. Busca "# PASAJEROS", lee lineas siguientes hasta otro '#'
 *    Cada linea: Color[int] X Y
 *    Ej: "1 4 2" → Persona VERDE en pos (4,2)
 *
 * Las lineas vacias se ignoran en todas las secciones.
 * Si el archivo no puede abrirse, imprime error y retorna.
 */
void MNivel::cargarArchivo(const std::string& nombreArchivo) {
    std::ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (linea.empty()) continue;

        // Detectar encabezados de seccion
        if (linea[0] == '#') {
            // --- SECCION DIMENSIONES ---
            if (linea.find("DIMENSIONES") != std::string::npos) {
                std::getline(archivo, linea);
                std::stringstream ss(linea);
                ss >> ancho >> alto;
            }
            // --- SECCION VEHICULOS ---
            else if (linea.find("VEHICULOS") != std::string::npos) {
                while (std::getline(archivo, linea)) {
                    if (linea.empty()) continue;
                    if (linea[0] == '#') {
                        // --- SECCION PASAJEROS (anidada dentro del bucle de vehiculos) ---
                        if (linea.find("PASAJEROS") != std::string::npos) {
                            while (std::getline(archivo, linea)) {
                                if (linea.empty()) continue;
                                if (linea[0] == '#') break; // siguiente seccion
                                std::stringstream ss(linea);
                                int color, x, y;
                                if (ss >> color >> x >> y) {
                                    personas.push_back(Persona(static_cast<colores>(color), x, y));
                                }
                            }
                        }
                        break; // sale del bucle de vehiculos
                    }
                    // Parsear linea de vehiculo: Tipo Color X Y Orientacion Tamano
                    std::stringstream ss(linea);
                    char tipo;
                    int color, x, y;
                    char orientacion;
                    int tam;
                    ss >> tipo >> color >> x >> y >> orientacion >> tam;
                    vehiculos.push_back(
                        Vehiculo(static_cast<colores>(color), tam, x, y, orientacion)
                    );
                }
            }
        }
    }

    archivo.close();
    std::cout << "Nivel cargado: " << ancho << "x" << alto
              << ", " << vehiculos.size() << " vehiculos, "
              << personas.size() << " pasajeros" << std::endl;
}

/**
 * @brief Obtiene el vector de personas del nivel (referencia modificable)
 * @return Referencia al vector de Persona
 */
std::vector<Persona>& MNivel::getPersonas() {
    return personas;
}

/**
 * @brief Obtiene el vector de vehiculos del nivel (referencia modificable)
 * @return Referencia al vector de Vehiculo
 */
std::vector<Vehiculo>& MNivel::getVehiculos() {
    return vehiculos;
}

/**
 * @brief Obtiene el ancho del tablero
 * @return Ancho en cantidad de casillas
 */
int MNivel::getAncho() const {
    return ancho;
}

/**
 * @brief Obtiene el alto del tablero
 * @return Alto en cantidad de casillas
 */
int MNivel::getAlto() const {
    return alto;
}
