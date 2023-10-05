// main.h

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <string>
#include <functional>


struct Nodo {
    int numero;
    std::string frase;
    std::function<void(std::vector<int>)> funcion_v;
    std::function<void(std::string, std::string)> funcion_ft;
    std::function<void(std::string, std::string)> funcion_io;
    Nodo *siguiente;
};

struct User {
    std::string nombre;
    std::string tipo;
    std::vector<int> permisos;
};

// Declaraciones de funciones
User verificarUsuario(std::string nombre, std::string ruta, std::string rutaPermisos);
std::vector<int> permisosInput(std::string permisosStr);
void permisosTxt(User& usuario);
void sumatoria(std::vector<int> v);
void promedio(std::vector<int> v);
void moda(std::vector<int> v);
void contar(std::vector<int> v);
void leerMenu(Nodo *&cabeza, std::string ruta, std::vector<int> v, std::string f, std::string t, std::string i, std::string o);
void salir(std::vector<int> v);
void agregar(std::string ruta, std::string texto);
void indefinido(std::vector<int> v);
void crear(std::string ruta_nombre, std::string texto);
void contarPalabras(const std::string& inputPath, const std::string& outputPath);
bool isFileLargerThan1MB(const std::string &file_path);

#endif // MAIN_H
