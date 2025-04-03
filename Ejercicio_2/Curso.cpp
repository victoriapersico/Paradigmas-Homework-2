#include "Curso.h"
using namespace std;

Curso::Curso(string nombre):nombre(nombre) {} //constructor

string Curso::obtener_nombre() const{
    return nombre;
}

//Shallow Copy. Constructor de copia que recibe otro Curso como parámetro
Curso::Curso(const Curso&copia) : max_estudiantes(copia.max_estudiantes), estudiantes(copia.estudiantes){ }//inicializo const size_t max_estudiantes con misma cantidad de max_estudiantes del otro curso. Como max_estudiantes es una const, lo inicializo en lista de inicializacion

void Curso::inscribir(shared_ptr<Curso> curso,shared_ptr<Estudiante> estudiante, float nota){
    if (curso->estudiantes.size()>=curso->max_estudiantes){
        throw runtime_error("\nError: El curso esta lleno, no se puede inscribir al estudiante.\n");
    }
    curso->estudiantes.push_back(estudiante); //con push back hago inserciones (no ordenadas alfabeticamente) pero en O(1)
    estudiante->inscribirse_en_curso(curso, nota);
}

shared_ptr<Estudiante> Curso::buscar_legajo(int legajo) { 
    for(auto &it:estudiantes){
        if(it->obtener_legajo()==legajo){
            return it;
        }
    }
    return nullptr;
}

void Curso::desinscribir(int legajo) {
    for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
        if ((*it)->obtener_legajo() == legajo) {  
            estudiantes.erase(it);
            cout << "\nEstudiante desinscripto con éxito.\n";
            return;
        }
    }
    cout << "\nEstudiante no fue encontrado en el curso.\n";
}

bool Curso::curso_completo() const{
    return estudiantes.size()==max_estudiantes;
}

void Curso::ordenar_estudiantes() {
    sort(estudiantes.begin(), estudiantes.end(), [](const shared_ptr<Estudiante>& a, const shared_ptr<Estudiante>& b) {
        return *a < *b;  //uso la sobrecarga de operator< de Estudiante
    });
}

void Curso::imprimir_estudiantes() const {
    if (estudiantes.empty()) {
        cout << "\nEl curso todavía no tiene estudiantes inscritos.\n";
        return;
    }
    for (const auto& estudiante : estudiantes){
        cout << *estudiante << endl;  //usa operator<< de Estudiante
    }
}