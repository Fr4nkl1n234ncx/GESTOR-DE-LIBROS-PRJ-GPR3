#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <cstring>
#include <limits>
#include "../libD/nmColor.h"
using namespace std;

class Libro {
public:
    Libro(int codigo, string titulo, string autor, int anioPublicacion)
        : codigo(codigo), titulo(titulo), autor(autor), anioPublicacion(anioPublicacion) {}

    int getCodigo() const { return codigo; }
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getAnioPublicacion() const { return anioPublicacion; }

private:
    int codigo;
    string titulo;
    string autor;
    int anioPublicacion;
};

class GestorLibros {
public:
    void agregarLibro(int codigo, string titulo, string autor, int anioPublicacion) {
        Libro libro(codigo, titulo, autor, anioPublicacion);
        libros.push_back(libro);
    }

    void printAnimatedText(const char* color, const char* text) {
        for (size_t i = 0; i < strlen(text); ++i) {
            printf("%s%c%s", color, text[i], RESET);
            this_thread::sleep_for(chrono::milliseconds(50));
        }
        cout << "\n";
    }

    bool buscarLibroPorCodigo(int codigo) {
        auto it = find_if(libros.begin(), libros.end(), [codigo](const Libro& libro) {
            return libro.getCodigo() == codigo;
        });

        if (it != libros.end()) {
            printAnimatedText(GREEN, "========================");
            printAnimatedText(MAGENTA, "Libro encontrado:");
            printAnimatedText(RED, "Codigo: "); printAnimatedText(LIGHT_CYAN, to_string(it->getCodigo()).c_str());
            printAnimatedText(RED, "Titulo: "); printAnimatedText(LIGHT_CYAN, it->getTitulo().c_str());
            printAnimatedText(RED, "Autor: "); printAnimatedText(LIGHT_CYAN, it->getAutor().c_str());
            printAnimatedText(RED, "A\xA4o de publicacion: "); printAnimatedText(LIGHT_CYAN, to_string(it->getAnioPublicacion()).c_str());
            printAnimatedText(GREEN, "========================");
            return true;
        } else {
            printAnimatedText(BLACK, "Libro no encontrado.");
            return false;
        }
    }

private:
    vector<Libro> libros;
};

int main() {
    GestorLibros gestor;

    gestor.agregarLibro(1001, "El Gran Gatsby", "F. Scott Fitzgerald", 1925);
    gestor.agregarLibro(1002, "1984", "George Orwell", 1949);
    gestor.agregarLibro(1003, "Don Quijote de la Mancha", "Miguel de Cervantes", 1605);
    gestor.agregarLibro(1004, "LATUYAPORSIACASO", "PEPE", 2023);

    while (true) {
        int codigoBusqueda;
        gestor.printAnimatedText(YELLOW, "Ingrese el codigo del libro a buscar: ");
        cin >> codigoBusqueda;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignora todos los caracteres hasta el próximo carácter de nueva línea

        if (gestor.buscarLibroPorCodigo(codigoBusqueda)) {
            string opcionLinea;
            gestor.printAnimatedText(YELLOW, "Desea buscar otro libro? (s/n): ");
            getline(cin, opcionLinea);

            if (opcionLinea.empty() || (opcionLinea[0] != 's' && opcionLinea[0] != 'S')) {
                break;
            }
        }

        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    return 0;
}