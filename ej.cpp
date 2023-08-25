#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <getopt.h>
#include <unordered_map>
#include <functional>
#include <sys/stat.h>

struct Nodo {
    int numero;
    std::string frase;
    std::function<void(std::vector<int>)> funcion_v;
    std::function<void(std::string, std::string)> funcion_ft;
    Nodo *siguiente;
};

using namespace std;

void sumatoria(vector<int> v);
void promedio(vector<int> v);
void moda(vector<int> v);
void contar(vector<int> v);
bool verificarUsuario(string nombre);
vector<int> permisosInput(string permisos);
vector<int> permisosTxt(string usuario);
void leerMenu(Nodo *&cabeza, string ruta, vector<int> v, string f, string t);
void salir(vector<int> v);
void agregar(string ruta, string texto);
void indefinido(vector<int> v);
void crear(string ruta, string texto);


int main(int argc, char* argv[]){
    int option;
    string usuario = "";
    string permisosStr = "";
    string f_ruta = "";
    string t_texto = "";

    while ((option = getopt(argc, argv, "u:v:f:t:")) != -1) {
        switch (option) {
            case 'u':
                usuario = optarg;
                break;
            case 'v':
                permisosStr = optarg;
                break;
            case 'f':
                f_ruta = optarg;
                break;
            case 't':
                t_texto = optarg;
                break;
            default:
                cerr << "Uso: " << argv[0] << " -u <nombre> -v <numeros> -f <archivo> -t <texto a escribir>" << endl;
                return EXIT_FAILURE;
        }
    }

    if (usuario == "" || permisosStr == "" || f_ruta == "" || t_texto == "") {
        cerr << "Debes proporcionar ambas opciones -u y -v." << endl;
        cerr << "Uso: " << argv[0] << " u <nombre> -v <numeros> -f <archivo> -t <texto a escribir>"  << endl;
        return EXIT_FAILURE;
    }

    size_t pos = f_ruta.find(';');
    if (pos == std::string::npos) {
        std::cerr << "Error: el argumento -f debe tener el formato ruta;nombre" << std::endl;
        return EXIT_FAILURE;
    }

    cout << "USUARIO: " << usuario << endl;

    if(!verificarUsuario(usuario)){
        return EXIT_FAILURE;
    }

    
    cout << "USUARIO: " << usuario << endl;

    vector<int> vectorInput = permisosInput(permisosStr);
    vector<int> permisostxt = permisosTxt(usuario);

    if(permisostxt.empty()){
        return EXIT_FAILURE;
    }
    cout << endl;
    sort(permisostxt.begin(), permisostxt.end());

    /*
    LEER MENU
    */
    Nodo *cabeza = nullptr;
    leerMenu(cabeza, "menu.txt", vectorInput, f_ruta, t_texto);


    while(true){
        
        for (Nodo *actual = cabeza; actual != nullptr; actual = actual->siguiente)
            cout << actual->numero << ") " << actual->frase << endl;

        int opcion;
        cout << "Ingrese opcion: ";
        cin >> opcion;
        system("clear"); 

        if(opcion >= 7){
            indefinido(vectorInput);
        }
        else{
            if (find(permisostxt.begin(), permisostxt.end(), opcion) == permisostxt.end() && opcion != 0){
                cout << "El usuario no tiene permiso para " << opcion << endl << endl;
            }
            else{
                for (Nodo *actual = cabeza; actual != nullptr; actual = actual->siguiente) {       
                    if(actual->numero == opcion){
                        if (actual->funcion_v) {
                            actual->funcion_v(vectorInput);
                        } else if (actual->funcion_ft) {
                            actual->funcion_ft(f_ruta, t_texto);
                            }
                        }
                    }
            }  
        }
    }
    

    // int opcion;
    // while(true){
    //     cout << "Ingrese opcion: ";
    //     cin >> opcion;

    //     if(opcion >= 7){
    //         indefinido(vectorInput);
    //     }
    //     else{
    //         if (find(permisostxt.begin(), permisostxt.end(), opcion) == permisostxt.end() && opcion != 0){
    //             cout << "El usuario no tiene permiso para " << opcion << endl << endl;
    //         }
    //         else{
    //             for (Nodo *actual = cabeza; actual != nullptr; actual = actual->siguiente) {       
    //                 if(actual->numero == opcion){
    //                     if (actual->funcion_v) {
    //                         actual->funcion_v(vectorInput);
    //                     } else if (actual->funcion_ft) {
    //                         actual->funcion_ft(f_ruta, t_texto);
    //                         }
    //                     }
    //                 }
    //         }  
    //     }
    // }
    
    return EXIT_SUCCESS;

}


bool verificarUsuario(string name){
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
        return EXIT_FAILURE;
        return 1;
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string token;
        vector<string> nombres;

        while (getline(iss, token, ';')) {
            nombres.push_back(token);
        }

        for (const string& nombre : nombres) {
            if (nombre == name) {
                cout << "El nombre '" << name << "' está en el archivo." << endl;
                archivo.close();
                return true;
            }
        }
    }

    cout << "El nombre '" << name << "' no se encontró en el archivo." << endl;
    archivo.close();
    return false;
}

vector<int> permisosInput(string permisosStr){
    size_t startPos = 0; 
    size_t endPos = permisosStr.find(',');
    vector<int> permisos;

    while (endPos != string::npos) {
        int number = stoi(permisosStr.substr(startPos, endPos - startPos));
        permisos.push_back(number);
        
        startPos = endPos + 1;
        endPos = permisosStr.find(',', startPos);
    }
    
    if (startPos < permisosStr.length()) {
        int number = stoi(permisosStr.substr(startPos));
        permisos.push_back(number);
    }

    // for (int num : permisos) {
    //     cout << num << " ";
    // }

    return permisos;
}

vector<int> permisosTxt(string nombre) {
    vector<int> numeros;
    
    ifstream archivo("permisos.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return numeros; // Devolver vector vacío en caso de error
    }
    
    string linea;
    while (getline(archivo, linea)) {
        size_t separador = linea.find(';');
        if (separador != string::npos) {
            string nombreEnArchivo = linea.substr(0, separador);
            if (nombreEnArchivo == nombre) {
                string numerosStr = linea.substr(separador + 1);
                if (numerosStr.empty()) {
                    cerr << "El usuario no tiene permisos." << endl;
                    archivo.close();
                    exit(1); // Terminar el programa con un código de error
                }
                size_t pos = 0;
                while ((pos = numerosStr.find(',')) != string::npos) {
                    numeros.push_back(stoi(numerosStr.substr(0, pos)));
                    numerosStr.erase(0, pos + 1);
                }
                numeros.push_back(stoi(numerosStr));
                break;
            }
        }
    }
    
    archivo.close();
    return numeros;
}

void sumatoria(vector<int> v){
    int suma = 0;

    for (int num : v) {
        suma += num;
    }

    cout << "La suma de los elementos es: " << suma << endl;
    cout << endl;
}

void promedio(vector<int> v){
    float suma = 0;

    for(int num: v){ 
        suma += num;
    }

    cout << "El promedio de los elementos es: " << suma/v.size() << endl;
    cout << endl;
}

void moda(vector<int> v) {
    unordered_map<int, int> frequency;
    for (int num : v) {
        frequency[num]++;
    }

    int maxFrequency = 0;
    int moda = 0;

    for (const auto& pair : frequency) {
        if (pair.second > maxFrequency) {
            maxFrequency = pair.second;
            moda = pair.first;
        }
    }

    cout << "La moda es " << moda << endl;
    cout << endl;
}

void contar(vector<int> v) {
    unordered_map<int, int> counts;

    for (int num : v) {
        counts[num]++;
    }

    for (const auto& pair : counts) {
        cout << "Cantidad de " << pair.first << ": " << pair.second << endl;
    }
    cout << endl;
}


void leerMenu(Nodo *&cabeza, string ruta, vector<int> v, string f, string t){
    ifstream archivo(ruta);
    string linea;
    // Nodo *cabeza = nullptr;

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string numero, frase, funcion;
        getline(ss, numero, ',');
        getline(ss, frase, ',');
        getline(ss, funcion, ',');

        if(funcion == "sumatoria"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(sumatoria, v), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "promedio"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(promedio, v), nullptr , cabeza};
            cabeza = nuevo;
        }
        if(funcion == "moda"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(moda, v), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "contar"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(contar, v), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "agregar"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, nullptr, bind(agregar, f, t), cabeza};
            cabeza = nuevo;
        }
        if(funcion == "salir"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(salir, v), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "indefinido"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(indefinido, v), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "crear"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, nullptr, bind(crear, f, t), cabeza};
            cabeza = nuevo;
        }
    }

    // Imprimir la lista enlazada
    // for (Nodo *actual = cabeza; actual != nullptr; actual = actual->siguiente) {
    //     cout << actual->numero << ") " << actual->frase << endl;
    // }

}

void salir(vector<int> v){
    return exit(1);
}


void crear(std::string ruta_nombre, std::string texto) {
    size_t pos = ruta_nombre.find(';');
    if (pos != std::string::npos) {
        std::string ruta = ruta_nombre.substr(0, pos);
        std::string nombre = ruta_nombre.substr(pos + 1);
        
        mkdir(ruta.c_str(), 0755);
        std::ifstream archivoExistente(ruta + "/" + nombre);
        if (archivoExistente.good()) {
            std::cout << "El archivo ya existe" << std::endl << endl;
        } else {
            std::ofstream archivo(ruta + "/" + nombre);
            cout << "Archivo creado exitosamente" << endl << endl;
        }
    } else {
        std::cerr << "Error: el argumento debe tener el formato ruta;nombre" << std::endl;
        return exit(1);
    }
}

void agregar(string ruta_nombre, string texto){
    size_t pos = ruta_nombre.find(';');
    if (pos != std::string::npos) {
        std::string ruta = ruta_nombre.substr(0, pos);
        std::string nombre = ruta_nombre.substr(pos + 1);

    
        std::ifstream archivoExistente(ruta + "/" + nombre);
        if (archivoExistente.good()) {
            ofstream archivo(ruta + "/" + nombre, ios_base::app);
            archivo << texto;
            cout << "Texto agregado correctamente" << endl << endl;
        } else {
            cout << "El archivo no existe" << endl << endl;
        }

    } else {
        std::cerr << "Error: el argumento debe tener el formato ruta;nombre" << std::endl;
        return exit(1);
    }
}

void indefinido(vector<int> v){
    cout << "Funcion no implementada" << endl << endl;
}