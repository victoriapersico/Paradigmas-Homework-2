#include "Estudiante.h"
#include "Curso.h"

Estudiante::Estudiante(string nombre, int legajo) : nombre(nombre), legajo(legajo) {}

string Estudiante::obtener_nombre() const {
    return nombre;
}

int Estudiante::obtener_legajo() const {
    return legajo;
}

void Estudiante::inscribirse_en_curso(shared_ptr<Curso> curso, float nota) {
    cursos_notas.emplace_back(curso, nota);
}

void Estudiante::imprimir_cursos() const {
    if (cursos_notas.empty()) {
        cout << "\nEl estudiante no está inscrito en ninguna materia.\n";
        return;
    }
    cout << "\nMaterias de " << nombre << ":\n";
    for (const auto& par : cursos_notas) {
        cout << "Curso: " << par.first->obtener_nombre() << ", Nota: " << par.second << endl;
    }
}

float Estudiante::promedio() const{
    if (cursos_notas.empty()){ //Evito división por cero, en el caso que estudiante no está anotado en ningún curso.
        return 0;
    }
    float promedio=0;
    for (const auto& notas : cursos_notas){
        promedio+=notas.second;
    }
    return (promedio/cursos_notas.size());
}
bool Estudiante::operator<(const Estudiante& otro) const {
    return nombre < otro.nombre;  //ordeno alfabéticamente, un estudiante es menor < a otro si su nombre es menor alfabeticamente
}
ostream& operator<<(ostream& os, const Estudiante&estudiante){
    os<<"\nNombre completo: "<<estudiante.nombre<<", Legajo: "<<estudiante.legajo; //Explica el formato para imprimir a 1 estudiante
    return os;
}