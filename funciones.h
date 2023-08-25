// main.h

#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <string>
#include <functional>

struct Nodo {
    int numero;
    std::string frase;
    std::function<void(std::vector<int>)> funcion_v;
    std::function<void(std::string, std::string)> funcion_ft;
    Nodo *siguiente;
};

// Declaraciones de funciones
bool verificarUsuario(std::string nombre);
std::vector<int> permisosInput(std::string permisosStr);
std::vector<int> permisosTxt(std::string usuario);
void sumatoria(std::vector<int> v);
void promedio(std::vector<int> v);
void moda(std::vector<int> v);
void contar(std::vector<int> v);
void leerMenu(Nodo *&cabeza, std::string ruta, std::vector<int> v, std::string f, std::string t);
void salir(std::vector<int> v);
void agregar(std::string ruta, std::string texto);
void indefinido(std::vector<int> v);
void crear(std::string ruta_nombre, std::string texto);

#endif // MAIN_H
