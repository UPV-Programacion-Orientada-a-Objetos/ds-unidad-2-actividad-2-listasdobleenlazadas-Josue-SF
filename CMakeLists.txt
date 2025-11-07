cmake_minimum_required(VERSION 3.10)
project(PRT7_Decoder CXX)

# Requisito: Especificar el estándar C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Definir todos los archivos fuente
set(SOURCE_FILES
    main.cpp
    Nodo.h
    RotorDeMapeo.h
    ListaDeCarga.h
    TramaBase.h
    TramaLoad.h
    TramaMap.h
)

# Crear el ejecutable
add_executable(prt7_decoder ${SOURCE_FILES})

# Opcional: Para facilitar la compilación y ejecución
target_compile_features(prt7_decoder PUBLIC cxx_std_17)

# Para compilar:
# mkdir build
# cd build
# cmake ..
# make
# sudo ./prt7_decoder
