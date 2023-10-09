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
#include "funciones.h" // Incluye el archivo de encabezado


using namespace std;

void cargarVariablesEnv() {
    const char* envFile = "/home/edgardo/Programacion/INFO-189_2/rutas.env";
    ifstream file(envFile);
    if (!file) {
        cerr << "No se pudo abrir el archivo .env" << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        size_t equalsPos = line.find('=');
        if (equalsPos != string::npos) {
            string key = line.substr(0, equalsPos);
            string value = line.substr(equalsPos + 1);
            setenv(key.c_str(), value.c_str(), 1);
        }
    }

    file.close();
}


int main(int argc, char* argv[]){
    cargarVariablesEnv();
    const char* rutaPermisos = getenv("permisos");
    const char* rutaUsuarios = getenv("usuarios");
    const char* rutaMenu = getenv("menu");

    string EXTENTION = getenv("EXTENTION");
    string PATH_FILES_IN = getenv("PATH_FILES_IN");
    string PATH_FILES_OUT = getenv("PATH_FILES_OUT");
    string AMOUNT_THREADS = getenv("AMOUNT_THREADS");
    string INDEX = getenv("INVERTED_INDEX_FILE");

    if(PATH_FILES_IN == PATH_FILES_OUT){
        cout << "ERROR\nPATH_FILES_IN == PATH_FILES_OUT" << endl;
        exit(1);
    }


    int option;
    string usuario = "";
    string permisosStr = "";
    string f_ruta = "";
    string t_texto = "";
    string ruta_input = "";
    string ruta_output = "";

    while ((option = getopt(argc, argv, "u:v:f:t:i:o:")) != -1) {
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
            case 'i':
                ruta_input = optarg;
                break;
            case 'o':
                ruta_output = optarg;
                break;                                
            default:
                cerr << "Uso: " << argv[0] << " -u <nombre> -v <numeros> -f <archivo> -t <texto a escribir> -i <ruta_input> -o <ruta_output>" << endl;
                return EXIT_FAILURE;
        }
    }

    if (usuario == "" || permisosStr == "" || f_ruta == "" || t_texto == "" || ruta_input ==  "" || ruta_output == "") {
        cerr << "Uso: " << argv[0] << " -u <nombre> -v <numeros> -f <archivo> -t <texto a escribir> -i <ruta_input> -o <ruta_output>"  << endl;
        return EXIT_FAILURE;
    }

    size_t pos = f_ruta.find(';');
    if (pos == std::string::npos) {
        std::cerr << "Error: el argumento -f debe tener el formato ruta;nombre" << std::endl;
        return EXIT_FAILURE;
    }

    User user = verificarUsuario(usuario, rutaUsuarios, rutaPermisos);
    if(user.nombre == ""){
        cout << "EL USUARIO NO SE ENCUENTRA" << endl;
        return EXIT_FAILURE;
    }

    vector<int> vectorInput = permisosInput(permisosStr);

    

    if(user.permisos.empty()){
        cout << "EL USUARIO NO TIENE PERMISOS" << endl;
        return EXIT_FAILURE;
    }
    cout << endl;
    sort(user.permisos.begin(), user.permisos.end());

    /*
    LEER MENU
    */
    Nodo *cabeza = nullptr;
    leerMenu(cabeza, rutaMenu, vectorInput, f_ruta, t_texto, ruta_input, ruta_output);

    bool seleccionado = false;

    while(true){
        cout << "USUARIO: " << user.nombre << " - " << user.tipo << endl;
        
        for (Nodo *actual = cabeza; actual != nullptr; actual = actual->siguiente){
            cout << actual->numero << ") " << actual->frase << endl;
        }
    
        int opcion;
        cout << "Ingrese opcion: ";
        cin >> opcion;
        system("clear"); 
        


        if(opcion > cabeza->numero){
            cout << "Opción inválida" << endl << endl;
        }
        else{

            if (find(user.permisos.begin(), user.permisos.end(), opcion) == user.permisos.end() && opcion != 0){
                cout << "El usuario no tiene permiso para " << opcion << endl << endl;
            }
            else{
                if(opcion == 9 && seleccionado == false){
                    cout << "Opción no disponible, ejecute primero 8)" << endl << endl;
                }
                else{
                    if(opcion == 9){
                        string comando = "./funciones_externas/crearIndice " + INDEX + " "  + " " + PATH_FILES_OUT;
                        system(comando.c_str());
                    }
                    else if(opcion == 8){
                        string comando = "./funciones_externas/contarPalabras " + EXTENTION + " " + PATH_FILES_IN + " " + PATH_FILES_OUT + " " + AMOUNT_THREADS;
                        system(comando.c_str());
                        
                        seleccionado = true;
                    }
                    else{
                        for (Nodo *actual = cabeza; actual != nullptr; actual = actual->siguiente) {       
                            if(actual->numero == opcion){
                                if (actual->funcion_v) {
                                    actual->funcion_v(vectorInput);
                                } else if (actual->funcion_ft) {
                                    actual->funcion_ft(f_ruta, t_texto);
                                }
                                else{
                                    actual->funcion_io(ruta_input, ruta_output);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    
    return EXIT_SUCCESS;

}