#ifndef CURSO_H
#define CURSO_H

#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include "Estudiante.h"

using namespace std;

class Curso{
    private:
        string nombre;
        vector<shared_ptr<Estudiante>> estudiantes;
        const size_t max_estudiantes = 20;

    public:
        Curso(string nombre);
        string obtener_nombre() const;
        Curso(const Curso& copia);
        void inscribir(shared_ptr<Curso> curso,shared_ptr<Estudiante> estudiante, float nota);
        shared_ptr<Estudiante> buscar_legajo(int legajo);
        void desinscribir(int legajo);
        bool curso_completo() const;
        void ordenar_estudiantes();
        void imprimir_estudiantes() const;
};

#endif