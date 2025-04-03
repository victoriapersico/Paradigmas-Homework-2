#include "Curso.h"
#include "Estudiante.h"

void menu(){

    vector<shared_ptr<Curso>> materia = {
        make_shared<Curso>("Física"),
        make_shared<Curso>("Paradigmas"),
        make_shared<Curso>("Probabilidad")
    };
    vector<shared_ptr<Estudiante>> estudiantes_materia;

    while (true){
        cout<<"\nMenú:\n";
        cout<< "\n1. Inscribir estudiante.\n";
        cout << "2. Desinscribir estudiante.\n";
        cout << "3. Buscar por legajo.\n";
        cout << "4. Disponibilidad vacante curso.\n";
        cout << "5. Ordenar estudiantes de un curso alfabéticamente.\n";
        cout << "6. Imprimir estudiantes de un curso.\n";
        cout << "7. Salir del menú.\n";
        cout<<"\nElija una opción:\n";

        int respuesta;
        cin>>respuesta;

        if (respuesta == 1) {
            string nombre;
            int legajo, curso_index;
            float nota;

            cout<< "\nIngrese el nombre del estudiante: ";
            cin>>nombre;
            cout<< "\nIngrese el legajo del estudiante: ";
            cin>>legajo;
            cout << "\nIngrese la nota del estudiante: ";
            cin >> nota;

            cout << "\nSeleccione un curso:\n";
            for (size_t i = 0; i < materia.size(); i++) {
                cout << i + 1 << ". " << materia[i]->obtener_nombre() << endl;
            }
            cout << "\nIngrese el número del curso: ";
            cin >> curso_index;

            if (curso_index < 1 || curso_index > materia.size()) {
                cout << "\nEl curso no válido.\n";
                continue;
            }

            shared_ptr<Estudiante> estudiante = make_shared<Estudiante>(nombre, legajo);
            estudiantes_materia.push_back(estudiante);

            try {
                shared_ptr<Curso> curso_seleccionado = materia[curso_index-1];
                curso_seleccionado->inscribir(curso_seleccionado, estudiante, nota);
                cout << "\nEstudiante inscrito correctamente en: "<<materia[curso_index - 1]->obtener_nombre()<<".\n";
            } catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
        }

        else if (respuesta == 2) {
            int legajo,curso_index;
            cout << "\nIngrese el legajo del estudiante a desinscribir: ";
            cin >> legajo;
            
            cout<<"\nSeleccione un curso:\n";
            for(size_t i=0;i<materia.size();i++){
                cout<<i+1<<". "<<materia[i]->obtener_nombre()<<endl;
            }
            cout<<"\nIngrese el número del curso";
            cin>>curso_index;

            if(curso_index<1 || curso_index>materia.size()){
                cout<<"\nEl curso no es válido.\n";
                continue;
            }
            materia[curso_index-1]->desinscribir(legajo);
        }

        else if (respuesta == 3) {
            int legajo, curso_index;
            cout << "\nIngrese el legajo a buscar: ";
            cin >> legajo;

            cout << "\nSeleccione el curso para buscar:\n";
            for (size_t i = 0; i < materia.size(); i++) {
                cout << i + 1 << ". " << materia[i]->obtener_nombre() << endl;
            }
            cout << "\nIngrese el número del curso: ";
            cin >> curso_index;

            if (curso_index < 1 || curso_index > materia.size()) {
                cout << "\nCurso no válido.\n";
                continue;
            }

            if (materia[curso_index - 1]->buscar_legajo(legajo)) {
                cout << "\nEl estudiante está inscrito en " << materia[curso_index - 1]->obtener_nombre() << ".\n";
            } else {
                cout << "\nEl estudiante no está inscrito en el curso seleccionado.\n";
            }
        }

        else if (respuesta == 4) {
            int curso_index;
            cout<<"\nSeleccione el curso:\n";
            for (size_t i=0; i<materia.size();i++){
                cout<<i+1<<". "<<materia[i]->obtener_nombre()<<endl;
            }
            cout<<"\nIngrese el número del curso:";
            cin>>curso_index;
            
            if(curso_index-1||curso_index>materia.size()){
                cout<<"\nCurso no válido.\n";
                continue;
            }

            if (materia[curso_index-1]->curso_completo()) {
                cout << "\nEl curso está completo.\n";
            } else {
                cout << "\nEl curso tiene vacantes disponibles.\n";
            }
        }

        else if (respuesta == 5) {
            int curso_index;
            cout<<"\nSeleccione un curso:\n";
            for(size_t i=0; i<materia.size(); i++){
                cout<<i+1<<". "<<materia[i]->obtener_nombre()<<endl;
            }
            cout<<"\nIngrese el número del curso:";
            cin>>curso_index;
            if(curso_index-1||curso_index>materia.size()){
                cout<<"\nCurso no válido.\n";
                continue;
            }
            materia[curso_index-1]->ordenar_estudiantes();
            cout << "\nEstudiantes ordenados alfabeticamente en: "<<materia[curso_index-1]->obtener_nombre()<<".\n";
        }

        else if(respuesta==6){
            int curso_index;
            cout<<"\nSeleccione un curso:\n";
            for(size_t i=0; i<materia.size(); i++){
                cout<<i+1<<". "<<materia[i]->obtener_nombre()<<endl;
            }
            cout<<"\nIngrese el número del curso:";
            cin>>curso_index;
            if(curso_index-1||curso_index>materia.size()){
                cout<<"\nCurso no válido.\n";
                continue;
            }

            materia[curso_index-1]->imprimir_estudiantes();
        }

        else if (respuesta==7) {
            cout << "\nCerrando el programa.\n";
            break;
        }

        else {
            cout << "\nEsa opción no es válida, intente de nuevo.\n";
        }
    }
};

int main() {
    menu();
    return 0;
}