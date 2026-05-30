# Bus Escape: Traffic Jam C++ Edition

Juego de logica estilo "Traffic Jam" donde debes mover vehiculos para recoger
pasajeros antes de que todos los vehiculos queden estacionados.

## Requisitos

- **Windows 10 o 11** (64 bits)
- **Git** para clonar el repositorio (opcional, puedes descargar el ZIP)
- **Compilador C++** (g++ de MSYS2, MinGW, o similar con soporte C++17)

## Como descargar el proyecto

### Opcion 1: Clonar con Git (recomendado)

Abre una terminal (PowerShell o CMD) y ejecuta:

```
git clone https://github.com/tu-usuario/BusEscape.git
cd BusEscape
```

### Opcion 2: Descargar ZIP

1. Ve a la pagina del repositorio en GitHub
2. Haz clic en el boton verde "Code"
3. Selecciona "Download ZIP"
4. Extrae el ZIP en una carpeta de tu computadora
5. Abre una terminal en esa carpeta

## Como compilar (generar el ejecutable)

### Con MSYS2 UCRT64 (recomendado para Windows)

1. Instala MSYS2 desde https://www.msys2.org/
2. Abre "MSYS2 UCRT64" desde el menu de inicio
3. Instala el compilador ejecutando:
   ```
   pacman -S mingw-w64-ucrt-x86_64-gcc
   ```
4. Navega a la carpeta del proyecto:
   ```
   cd /c/Users/TuUsuario/Desktop/Traffic\ Jam/BusEscape
   ```
   (ajusta la ruta segun donde hayas descargado el proyecto)
5. Compila el juego:
   ```
   g++ -std=c++17 -I include -o BusEscape.exe src/*.cpp
   ```
6. Si no hay errores, se habra creado el archivo `BusEscape.exe`

### Con MinGW (alternativa)

Si tienes MinGW instalado, abre una terminal normal (PowerShell o CMD)
en la carpeta del proyecto y ejecuta:

```
g++ -std=c++17 -I include -o BusEscape.exe src/*.cpp
```

## Como jugar

1. Asegurate de estar en la carpeta del proyecto (donde esta BusEscape.exe)
2. Ejecuta el juego:

   En PowerShell o CMD:

   ```
   BusEscape.exe
   ```

   En MSYS2:

   ```
   ./BusEscape.exe
   ```

3. El juego te pedira seleccionar un nivel (1=Facil, 2=Medio, 3=Dificil)
4. Se mostrara el tablero con los vehiculos y la lista de pasajeros
5. Para mover un vehiculo:
   - Escribe el numero del vehiculo y presiona Enter
   - Escribe la direccion: W (arriba), S (abajo), A (izquierda), D (derecha)
   - Escribe cuantos pasos moverlo y presiona Enter
6. Ganas cuando recoges a todos los pasajeros
7. Pierdes cuando todos los vehiculos se estacionan y aun hay pasajeros

## Estructura del proyecto

```
BusEscape/
  include/          Archivos de cabecera (.h)
    Objeto.h        Clase base (color)
    Vehiculo.h      Vehiculos que se mueven en el tablero
    Persona.h       Pasajeros que esperan ser recogidos
    MNivel.h        Modelo: carga niveles desde archivos
    CJuego.h        Controlador: logica del juego
    VDisplay.h      Vista: dibuja el tablero en consola
  src/              Codigo fuente (.cpp)
    main.cpp        Punto de entrada del programa
    Objeto.cpp
    Vehiculo.cpp
    Persona.cpp
    MNivel.cpp      Lector de archivos de nivel
    CJuego.cpp      Motor del juego (movimiento, colisiones, parqueo)
    VDisplay.cpp    Renderizador del tablero
  niveles/          Archivos de nivel (.txt)
    nivel1.txt      6x6 - 3 vehiculos - 4 pasajeros
    nivel2.txt      8x8 - 4 vehiculos - 6 pasajeros
    nivel3.txt      10x10 - 7 vehiculos - 8 pasajeros
  BusEscape.exe     Ejecutable (se genera al compilar)
  CMakeLists.txt    Configuracion para CMake (opcional)
```

## Solucion de problemas

**"g++ no se reconoce como un comando"**

- No tienes un compilador de C++ instalado. Sigue los pasos de la seccion
  "Con MSYS2 UCRT64" arriba.

**"No se pudo abrir el archivo niveles/nivel1.txt"**

- Asegurate de ejecutar el juego desde la carpeta del proyecto
  (donde se encuentra la carpeta "niveles/").

**El juego se cierra inmediatamente**

- Ejecuta el juego desde una terminal en vez de hacer doble clic.
  Si haces doble clic, la ventana se cierra al terminar el programa.

## Creditos

Proyecto desarrollado como parte del curso de Programacion Orientada a Objetos
con C++17, aplicando el patron MVC (Modelo-Vista-Controlador).
Miembros:

- Juan Esteban Hoyos Ortiz - 2540054
- Juan José Montaño Dosman - 2538124
- Santiago Muñoz Bolaños - 2539226
