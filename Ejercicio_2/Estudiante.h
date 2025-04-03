#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

class Curso; // forward declaration para evitar problemas de dependencia circular

class Estudiante {
private:
    string nombre;
    int legajo;
    vector<pair<shared_ptr<Curso>, float>> cursos_notas;

public:
    Estudiante(string nombre, int legajo);

    string obtener_nombre() const;
    int obtener_legajo() const;
    
    void inscribirse_en_curso(shared_ptr<Curso> curso, float nota);
    void imprimir_cursos() const;
    float promedio() const;

    bool operator<(const Estudiante& otro) const;
    friend ostream& operator<<(ostream& os, const Estudiante& estudiante);
};

#endif // ESTUDIANTE_H
