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
#include <filesystem>
#include <thread>
#include <mutex>
#include <map>
#include <queue>
#include <unistd.h> // para usar getpid()


std::mutex cout_mutex;
using namespace std;

std::vector<std::string> lee_archivos(std::string ruta_input, const std::string& file_type);
void contarPalabras(const std::string &input_file, const std::string &output_path, int thread_id);

// Implementación de la función lee_archivos
vector<string> lee_archivos(string ruta_input, const string& file_type) {
    vector<string> archivos;

    if (!filesystem::is_directory(ruta_input)) {
        cerr << "La carpeta especificada no existe: " << ruta_input << endl;
        exit(EXIT_FAILURE);
    }

    for (const auto &entry : filesystem::directory_iterator(ruta_input)) {
        const string archivo = entry.path().string();

        if (filesystem::path(archivo).extension() == "." + file_type) {
            archivos.push_back(archivo);
        }
    }

    return archivos;
}

// Implementación de la función contarPalabras
void contarPalabras(const string &input_file, const string &output_path, int thread_id) {
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

    filesystem::path p(input_file);

    if (!filesystem::is_directory(output_path)) {
        cerr << "La carpeta especificada no existe: " << output_path << endl;
        exit(EXIT_FAILURE);
    }


    string output_file = output_path + "/" + p.stem().string() + p.extension().string();
    ifstream check_output_file(output_file);
    if (check_output_file.good()) {
    cout << "El archivo de salida ya existe " << "(" << output_file << ")"  << endl;
    return;
    }

    ofstream output_file_stream(output_file);
    for (const auto& entry : sorted_words) {
    output_file_stream << entry.first << "," << entry.second << endl;
    }

    output_file_stream.close();

    {
        
        std::lock_guard<std::mutex> lock(cout_mutex);
        pid_t pid = getpid();
        std::cout << "proceso pid=" << pid << " - " << input_file << " procesado por el thread " << thread_id << std::endl;
    }
}



int main(int argc, char* argv[]){
    if(argc > 5){
        cout << "El uso debe ser ./app extension input output threads" << endl; 
    }

    string ruta_input, ruta_output, file_type;
    int num_threads;

    file_type = argv[1];
    ruta_input = argv[2];
    ruta_output = argv[3];
    num_threads = stoi(argv[4]);

    if(num_threads > 10){
        cout << "La cantidad de threads no puede ser mayor a 10" << endl << endl;
        exit(EXIT_FAILURE);
    }


    vector<string> files = lee_archivos(ruta_input, file_type);

    cout << "THREADS A USAR: " << num_threads << endl;
    if(num_threads <= 0){
        cout << "ERROR, no se pueden usar " << num_threads << " threads" << endl;
        exit(EXIT_FAILURE);
    } cout << endl;

    vector<thread> threads;
    queue<string> work_queue;
    for (const string& file : files) {
        work_queue.push(file);
    }

    for (int i = 0; i < num_threads; ++i) {
        // cout << i << endl;
        threads.push_back(thread([&work_queue, ruta_output, i]() {
            while (true) {
                string file;
                {
                    lock_guard<mutex> lock(cout_mutex);
                    if (!work_queue.empty()) {
                        file = work_queue.front();
                        work_queue.pop();
                    } else {
                        break;  // No hay más archivos para procesar.
                    }
                }
                contarPalabras(file, ruta_output, i);
            }
        }));
    }

    for (auto& thread : threads) {
        thread.join();
    }


    return EXIT_SUCCESS;
}  