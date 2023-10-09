#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <filesystem>
#include <unistd.h> 

using namespace std;



struct FileInfo {
    std::string filename;
    int count;
};

// Tipo de datos para el mapa principal
typedef std::map<std::string, std::vector<FileInfo>> WordMap;

// Función para procesar un archivo y actualizar el mapa
void processFile(const std::string& filename, WordMap& wordMap) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::string word;
        int count;
        if (!(std::getline(ss, word, ',') && ss >> count)) {
            // Error al leer la línea
            continue;
        }

        FileInfo fileInfo = {filename, count};
        wordMap[word].push_back(fileInfo);
    }
    file.close(); 
}

// Función para escribir el mapa en un archivo
void writeIndex(const std::string& filename, const WordMap& wordMap) {
    pid_t pid = getpid();

    ifstream checkFile(filename);
    if (checkFile.is_open()) {
        std::cerr << "El archivo ya existe: " << filename << std::endl;
        return;
    }

    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
        return;
    }

    for (const auto& pair : wordMap) {
        file << pair.first << ":";
        for (const FileInfo& fileInfo : pair.second) {
            file << "(" << fileInfo.filename << "," << fileInfo.count << ");";
        }
        file << "\n";
    }
    cout << "El proceso pid=" << pid << " generó el archivo=" << filename << endl;
}

vector<string> lee_archivos(string ruta_input) {
    vector<string> archivos;

    if (!filesystem::is_directory(ruta_input)) {
        cerr << "La carpeta especificada no existe: " << ruta_input << endl;
        exit(EXIT_FAILURE);
    }

    for (const auto &entry : filesystem::directory_iterator(ruta_input)) {
        const string archivo = entry.path().string();
        archivos.push_back(archivo);
    }

    return archivos;
}

int main(int argc, char* argv[]){
    if(argc > 3){
        cout << "El uso debe ser ./app input output" << endl;
    }
    string ruta_input = argv[2];
    string ruta_output = argv[1];

    WordMap wordMap;

    vector<string> files = lee_archivos(ruta_input);

    for (const string& file : files) {
        processFile(file, wordMap);
    }
    // Escribir el índice en un archivo
    writeIndex(ruta_output, wordMap);

    return 0;
}
