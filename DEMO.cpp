#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Clase Libro
class Libro {
public:
    Libro(int codigo, string titulo, string autor, int anioPublicacion)
        : codigo(codigo), titulo(titulo), autor(autor), anioPublicacion(anioPublicacion) {}

    int getCodigo() const {
        return codigo;
    }

    string getTitulo() const {
        return titulo;
    }

    string getAutor() const {
        return autor;
    }

    int getAnioPublicacion() const {
        return anioPublicacion;
    }

private:
    int codigo;
    string titulo;
    string autor;
    int anioPublicacion;
};

// Clase GestorLibros
class GestorLibros {
public:
    void agregarLibro(int codigo, string titulo, string autor, int anioPublicacion) {
        Libro libro(codigo, titulo, autor, anioPublicacion);
        libros.push_back(libro);
    }

    void buscarLibroPorCodigo(int codigo) {
        auto it = find_if(libros.begin(), libros.end(), [codigo](const Libro& libro) {
            return libro.getCodigo() == codigo;
        });

        if (it != libros.end()) {
            cout << "Libro encontrado:" << endl;
            cout << "Codigo: " << it->getCodigo() << endl;
            cout << "Titulo: " << it->getTitulo() << endl;
            cout << "Autor: " << it->getAutor() << endl;
            cout << "Ano de publicacion: " << it->getAnioPublicacion() << endl;
        } else {
            cout << "Libro no encontrado." << endl;
        }
    }

private:
    vector<Libro> libros;
};

// Función principal
int main() {
    GestorLibros gestor;

    // Agregar algunos libros de ejemplo
    gestor.agregarLibro(1001, "El Gran Gatsby", "F. Scott Fitzgerald", 1925);
    gestor.agregarLibro(1002, "1984", "George Orwell", 1949);
    gestor.agregarLibro(1003, "Don Quijote de la Mancha", "Miguel de Cervantes", 1605);

    // Buscar un libro por código
    int codigoBusqueda;
    cout << "Ingrese el codigo del libro a buscar: ";
    cin >> codigoBusqueda;
    gestor.buscarLibroPorCodigo(codigoBusqueda);

    return 0;
}
