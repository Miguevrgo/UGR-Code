cmake_minimum_required(VERSION 3.16)
project(practicafinal)

set(CMAKE_CXX_STANDARD 14)
set(BASE_FOLDER rutas_aereas)

include_directories(${BASE_FOLDER}/include)

add_library(image ${BASE_FOLDER}/src/imagen.cpp  ${BASE_FOLDER}/src/imagenES.cpp rutas_aereas/src/imagen.cpp
        rutas_aereas/include/imagen.h
        rutas_aereas/src/ruta_aerea.cpp
        rutas_aereas/src/punto.cpp
        rutas_aereas/include/punto.h
        rutas_aereas/src/ruta.cpp
        rutas_aereas/include/ruta.h
        rutas_aereas/src/almacen.cpp
        rutas_aereas/include/almacen.h
        rutas_aereas/src/pais.cpp
        rutas_aereas/include/pais.h
        rutas_aereas/src/paises.cpp
        rutas_aereas/include/paises.h)

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/pruebarotacion.cpp)
add_executable(pruebarotacion ${BASE_FOLDER}/src/pruebarotacion.cpp
        rutas_aereas/include/imagen.h)
target_link_libraries(pruebarotacion LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/pruebapegado.cpp)
add_executable(pruebapegado ${BASE_FOLDER}/src/pruebapegado.cpp
        rutas_aereas/include/imagen.h)
target_link_libraries(pruebapegado LINK_PUBLIC image)
endif()

if (EXISTS ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}/src/ruta_aerea.cpp)
add_executable(ruta_aerea ${BASE_FOLDER}/src/ruta_aerea.cpp
        rutas_aereas/include/imagen.h
        rutas_aereas/src/ruta_aerea.cpp
        rutas_aereas/src/punto.cpp
        rutas_aereas/include/punto.h
        rutas_aereas/src/ruta.cpp
        rutas_aereas/include/ruta.h
        rutas_aereas/src/almacen.cpp
        rutas_aereas/include/almacen.h
        rutas_aereas/src/pais.cpp
        rutas_aereas/include/pais.h
        rutas_aereas/src/paises.cpp
        rutas_aereas/include/paises.h)
target_link_libraries(ruta_aerea LINK_PUBLIC image)
endif()

# check if Doxygen is installed
find_package(Doxygen)
if (DOXYGEN_FOUND)
    # set input and output files
    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    # request to configure the file
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
    message("Doxygen build started")

    # note the option ALL which allows to build the docs together with the application
    add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/${BASE_FOLDER}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
else (DOXYGEN_FOUND)
    message("Doxygen need to be installed to generate the doxygen documentation")
endif (DOXYGEN_FOUND)
