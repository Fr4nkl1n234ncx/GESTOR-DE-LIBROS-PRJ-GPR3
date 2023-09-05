#include <iostream>
#include <fstream>
#include <iomanip>
#include <iomanip>
#include <unistd.h>
#include <windows.h>
#include <vector>
#include "../lib/patString.h"
#include <locale>

using namespace std;

const string pathDatos = "../../data/libros.txt";

struct libro
{
    string ID;
    string nombre;
    string fecha;
    string autor;
    string editorial;
    string descripcion;
};

enum color { azul = 1, verde, turqueza, rojo, rosa, amarillo};
string setColor(color c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return "";
}

vector <libro> libros;

// void buscarID()
// {
//     string id;
//     libro l;
//     getline(cin, id);
// }




void ingresarLibro()
{
    libro l;
    cout<<"Ingrese el ID" <<endl;
    getline(cin, l.ID);            
    cout<<"Ingrese el nombre del libro" <<endl;
    getline(cin, l.nombre);
    cout<<"Ingrese la fecha" <<endl;
    getline(cin, l.fecha);
    cout<<"Ingrese el autor" <<endl;
    getline(cin, l.autor);
    cout<<"Ingrese la editorial" <<endl;
    getline(cin, l.editorial);
    cout<<"Ingrese la descripcion" <<endl;
    getline(cin, l.descripcion);
    libros.push_back(l);    
}

bool showLibros()
{
    if(libros.empty())
    {
        cout <<setColor(rojo) <<endl <<setw(10)<<"\t\tNO HAY LIBROS" <<endl;
        return false;
    }

    cout << setColor(rosa) <<endl <<setw(10) <<"  ID\t" <<setw(5)<<" FECHA \t" <<setw(24)<<"\t AUTOR \t" <<setw(33)<<"\t NOMBRE \t"<<setw(30)<< " EDITORIAL \n";
    cout << setColor(turqueza);
    for (const auto& l : libros)
        cout <<endl <<setw(10)<<l.ID <<"\t" << setw(6)<<l.fecha << "\t" <<setw(25)<<l.autor << "\t" <<setw(35)<<l.nombre<< "\t" <<setw(30)<<l.editorial <<endl;

    return true;
}

bool showLibroFecha(string anio)
{
    bool encontrado = false;
    int n = 1;

    for (const auto& l : libros) {
        if (l.fecha == anio) {
             cout << "----------- Libro " << n << " -----------" <<endl;
            cout << "ID: " << l.ID << endl;
            cout << "AUTOR: " << l.autor << endl;
            cout << "NOMBRE: " << l.nombre << endl;
            cout << "FECHA: " << l.fecha << endl;
            cout << "EDITORIAL: " << l.editorial << endl;
            cout << "DESCRIPCION: " << l.descripcion << endl<<endl;
            n++;
            encontrado = true;
        }
    }

    if (!encontrado) {
        cout << setColor(rojo) << "NO HAY LIBROS" << endl;
    }

    return true;
}



bool saveLibro()
{
    int nElem = 0;
    fstream f;
    string line;
    int tamLibros = libros.size();

    cout << "savelibros:" << pathDatos << endl;
    f.open(pathDatos, ios_base::out);
    if (!f.is_open())
    {
        cout << endl << "Error al salvar el archivo: " << pathDatos << endl;
        return false;
    }
    f << " ID;autor;nombre;fecha;editorial;descripcion;" << endl;
    for (const auto& l : libros)
    {        
            f << l.ID << ";" << l.autor << ";" << l.nombre << ";" << l.fecha << ";" << l.editorial << ";" << l.descripcion;
            if (nElem!= (tamLibros-1))
                f <<endl;         
            nElem++;
   
    }
    return true;
}

void readArchivo()
{
    fstream f;
    string line;
    cout << "readArchivo:" << pathDatos << endl;
    f.open(pathDatos, ios_base::in);
    if (!f.is_open())
        cout << "Error al abrir el archivo:" << pathDatos << endl;
    
    libros.clear();
    
    getline(f, line);
    while(!f.eof())
    {
        struct libro c;
        vector<string> vDato;

        getline(f, line);
        vDato= SplitToVector(line, ';');

        c.ID            =               (vDato.at(0));   //              (vDato.at(0));
        c.autor         = ppToCapitalStr(vDato.at(1));   //ppToUpperStr  (vDato.at(1));
        c.nombre        =               (vDato.at(2));   //              (vDato.at(2));
        c.fecha         = ppToCapitalStr(vDato.at(3));   //ppToCapitalStr(vDato.at(3));
        c.editorial     = ppToCapitalStr(vDato.at(4));   //ppToCapitalStr(vDato.at(4));
        c.descripcion   =               (vDato.at(5));   //ppToCapitalStr(vDato.at(5));

        libros.push_back(c);

        
    }
}


void menu(int &opc)
{
    bool opcValida = false;
    do{
        cout << endl << setColor(azul) << "\t\tMENU" << endl;
        cout << setColor(verde)  <<"\t 1. Buscar libro por codigo"<< endl
            <<"\t 2. Buscar libro por fecha"<< endl
            <<"\t 3. Presentar libros"<< endl
            <<"\t 4. Agregar libro"<< endl
            <<"\t 5. Salir" << endl;

        try
        {
            cin >> opc;
            cin.ignore();  
            if (opc > 0 && opc <= 5)
            {
                opcValida = true;
                break;
            } 
            throw invalid_argument("Opc no valida");
        }
        catch(...)
        {
            cout << "\n    :( Opcion no valida... ";
            cin.ignore();
        }
    }while(!opcValida);
}

int main()
{
    string ano;
    libro datosL, nDatos;
    readArchivo();
    cout << "------------- GESTOR DE LIBROS ----" << endl;
    int eleccion = 0;
    int salir = false;
    do{
        menu(eleccion);
        fflush(stdin);  
        switch (eleccion)
        {
            case 1: 
                // Agregar lógica para buscar por código
                break;
            case 2: cout <<endl << "Ingrese la fecha de publicacion: ";
                    getline(cin, ano);
                    cout <<endl;
                    showLibroFecha(ano);
                break;
            case 3: showLibros();
                break;
            case 4: ingresarLibro();
                break;
            case 5: salir = true;
                break;
        }
        cout << endl;
    } while (!salir);
    saveLibro();
    return 0;
}
