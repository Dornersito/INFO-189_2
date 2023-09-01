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
#include "funciones.h"
#include <filesystem>
#include <locale>
#include <map>

using namespace std;


void permisosTxt(User& usuario, string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo permisos.txt" << endl;
        exit(EXIT_FAILURE);
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string token;
        vector<int> numbers;

        size_t semicolonPos = linea.find(';');

        string userType = linea.substr(0, semicolonPos);

        if(userType == usuario.tipo){
            string numberPart = linea.substr(semicolonPos + 1);
            stringstream ss(numberPart);
            string numberStr;

            while (getline(ss, numberStr, ',')) {
                int number = stoi(numberStr);
                numbers.push_back(number);
            }
            usuario.permisos = numbers;

            archivo.close();
            break;
        }
    }

    archivo.close();


}

User verificarUsuario(string name, string ruta, string rutaPermisos) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo usuarios.txt" << endl;
        exit(EXIT_FAILURE);
    }

    string linea;
    while (getline(archivo, linea)) {
        istringstream iss(linea);
        string token;
        vector<string> nombres;

        while (getline(iss, token, ';')) {
            nombres.push_back(token);
            // cout << token << endl;
        }

        string n, t;
        for (const string& nombre : nombres) {
            istringstream iss(nombre);
            getline(iss, n, ',');
            getline(iss, t);
            if (n == name) {
                archivo.close();
                User usuario = {n, t, {}};
                permisosTxt(usuario, rutaPermisos);
                return usuario;
            }
        }
    }

    archivo.close();
    User usuario = {"", "", {}};
    return usuario;
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


void leerMenu(Nodo *&cabeza, string ruta, vector<int> v, string f, string t, string i, string o){
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
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(sumatoria, v), nullptr, nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "promedio"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(promedio, v), nullptr , nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "moda"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(moda, v), nullptr, nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "contar"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(contar, v), nullptr, nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "agregar"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, nullptr, bind(agregar, f, t), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "salir"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(salir, v), nullptr, nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "indefinido"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, bind(indefinido, v), nullptr, nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "crear"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, nullptr, bind(crear, f, t), nullptr, cabeza};
            cabeza = nuevo;
        }
        if(funcion == "count_words"){
            Nodo *nuevo = new Nodo{stoi(numero), frase, nullptr, nullptr, bind(contarPalabras, i, o), cabeza};
            cabeza = nuevo;
        }
    }
}

void salir(vector<int> v){
    return exit(1);
}


void crear(string ruta_nombre, string texto) {
    size_t pos = ruta_nombre.find(';');
    if (pos != string::npos) {
        string ruta = ruta_nombre.substr(0, pos);
        string nombre = ruta_nombre.substr(pos + 1);
        
        mkdir(ruta.c_str(), 0755);
        ifstream archivoExistente(ruta + "/" + nombre);
        if (archivoExistente.good()) {
            cout << "El archivo ya existe" << endl << endl;
        } else {
            ofstream archivo(ruta + "/" + nombre);
            cout << "Archivo creado exitosamente" << endl << endl;
        }
    } else {
        cerr << "Error: el argumento debe tener el formato ruta;nombre" << endl;
        return exit(1);
    }
}

void agregar(string ruta_nombre, string texto){
    size_t pos = ruta_nombre.find(';');
    if (pos != string::npos) {
        string ruta = ruta_nombre.substr(0, pos);
        string nombre = ruta_nombre.substr(pos + 1);

    
        ifstream archivoExistente(ruta + "/" + nombre);
        if (archivoExistente.good()) {
            ofstream archivo(ruta + "/" + nombre, ios_base::app);
            archivo << texto;
            cout << "Texto agregado correctamente" << endl << endl;
        } else {
            cout << "El archivo no existe" << endl << endl;
        }

    } else {
        cerr << "Error: el argumento debe tener el formato ruta;nombre" << endl;
        return exit(1);
    }
}

void indefinido(vector<int> v){
    cout << "Funcion no implementada" << endl << endl;
}


void contarPalabras(const string &input_file, const string &output_file) {
  ifstream input_file_stream(input_file);
  if (!input_file_stream.is_open()) {
    cerr << "El archivo de entrada no existe." << endl << endl;
    return;
  }

  vector<string> words;

  string word;
  while (input_file_stream >> word) {
    words.push_back(word);
  }

  map<string, int> word_counts;

  for (const string &word : words) {
    if (word_counts.find(word) == word_counts.end()) {
      word_counts[word] = 0;
    }
    word_counts[word]++;
  }

  vector<pair<string, int>> sorted_words(word_counts.begin(), word_counts.end());
  sort(sorted_words.begin(), sorted_words.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second;
  });

  ifstream check_output_file(output_file);
  if (check_output_file.good()) {
    cout << "El archivo de salida ya existe." << endl << endl;
    return;
  }

  ofstream output_file_stream(output_file);
  for (const auto& entry : sorted_words) {
    output_file_stream << entry.first << ";" << entry.second << endl;
  }

  cout << "ARCHIVO CREADO" << endl << endl;

  output_file_stream.close();
}