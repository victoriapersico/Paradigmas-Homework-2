#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <algorithm>

using namespace std;
class Curso;

class Estudiante{
    private:
        string nombre;
        int legajo;
        vector<pair<shared_ptr<Curso>,float>> cursos_notas;
    
    public:
        Estudiante(string Nombre, int legajo):nombre(Nombre),legajo(legajo){}
        string obtener_nombre() const{
            return nombre;
        }

        int obtener_legajo() const{ //métodos llevan const porque no modifican el objeto
            return legajo;
        }

        void inscribirse_en_curso(Curso* curso, float nota) {
            cursos_notas.emplace_back(curso, nota);
        }

        void imprimir_cursos() const {
            if (cursos_notas.empty()) {
                cout << "\nEl estudiante no está inscrito en ninguna materia.\n";
                return;
            }
            cout << "\nMaterias de " << nombre << ":\n";
            for (const auto& par : cursos_notas) {
                cout << "Curso: " << par.first->obtener_nombre() << ", Nota: " << par.second << endl;
            }
        }

        float promedio() const{
            if (cursos_notas.empty()){ //Evito división por cero, en el caso que estudiante no está anotado en ningún curso.
                return 0;
            }
            float promedio=0;
            for (const auto& notas : cursos_notas){
                promedio+=notas.second;
            }
            return (promedio/cursos_notas.size());
        }
        bool operator<(const Estudiante& otro) const {
            return nombre < otro.nombre;  //ordeno alfabéticamente, un estudiante es menor < a otro si su nombre es menor alfabeticamente
        }
        friend ostream& operator<<(ostream& os, const Estudiante&estudiante){
            os<<"\nNombre completo: "<<estudiante.nombre<<", Legajo: "<<estudiante.legajo; //Explica el formato para imprimir a 1 estudiante
            return os;
        }
};

class Curso{
    private:
        string nombre;
        vector<shared_ptr<Estudiante>> estudiantes;
        const size_t max_estudiantes = 20;

    public:
        Curso(string nombre):nombre(nombre) {} //constructor
        
        string obtener_nombre() const{
            return nombre;
        }
        
        //Shallow Copy. Constructor de copia que recibe otro Curso como parámetro
        Curso(const Curso&copia) : max_estudiantes(copia.max_estudiantes){ //inicializo const size_t max_estudiantes con misma cantidad de max_estudiantes del otro curso. Como max_estudiantes es una const, lo inicializo en lista de inicializacion
            estudiantes = copia.estudiantes;
        }

        void inscribir(shared_ptr<Estudiante> estudiante, float nota){
            if (estudiantes.size()>=max_estudiantes){
                throw runtime_error("\nError: El curso esta lleno, no se puede inscribir al estudiante.\n");
            }
            estudiantes.push_back(estudiante); //con push back hago inserciones (no ordenadas alfabeticamente) pero en O(1)
            estudiante->inscribirse_en_curso(this, nota);
        }

        shared_ptr<Estudiante> buscar_legajo(int legajo){ 
            for(auto &it:estudiantes){
                if(it->obtener_legajo()==legajo){
                    return it;
                }
            }
            return nullptr;
        }

        void desinscribir(int legajo) {
            for (auto it = estudiantes.begin(); it != estudiantes.end(); ++it) {
                if ((*it)->obtener_legajo() == legajo) {  
                    estudiantes.erase(it);
                    cout << "\nEstudiante desinscripto con éxito.\n";
                    return;
                }
            }
            cout << "\nEstudiante no fue encontrado en el curso.\n";
        }
        
        bool curso_completo(){
            return estudiantes.size()==max_estudiantes;
        }

        void ordenar_estudiantes() {
            sort(estudiantes.begin(), estudiantes.end(), [](const shared_ptr<Estudiante>& a, const shared_ptr<Estudiante>& b) {
                return *a < *b;  //uso la sobrecarga de operator< de Estudiante
            });
        }
        
        void imprimir_estudiantes() const {
            if (estudiantes.empty()) {
                cout << "\nEl curso todavía no tiene estudiantes inscritos.\n";
                return;
            }
            for (const auto& estudiante : estudiantes){
                cout << *estudiante << endl;  //usa operator<< de Estudiante
            }
        }
};

void menu(){

    vector <Curso> materia = {Curso("Física"), Curso("Paradigmas"), Curso("Probabilidad")};
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
                cout << i + 1 << ". " << materia[i].obtener_nombre() << endl;
            }
            cout << "\nIngrese el número del curso: ";
            cin >> curso_index;

            if (curso_index < 1 || curso_index > materia.size()) {
                cout << "\nEl curso no válido.\n";
                continue;
            }

            shared_ptr<Estudiante> estudiante = make_shared<Estudiante>(nombre, legajo);
            estudiantes_materia.push_back(estudiante);

            auto estudiante = make_shared<Estudiante>(nombre, legajo);
            estudiantes_materia.push_back(estudiante);

            try {
                materia[curso_index-1].inscribir(estudiante,nota);
                cout << "\nEstudiante inscrito correctamente en: "<<materia[curso_index - 1].obtener_nombre()<<".\n";
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
                cout<<i+1<<". "<<materia[i].obtener_nombre()<<endl;
            }
            cout<<"\nIngrese el número del curso";
            cin>>curso_index;

            if(curso_index<1 || curso_index>materia.size()){
                cout<<"\nEl curso no es válido.\n";
                continue;
            }
            materia[curso_index-1].desinscribir(legajo);
        }

        else if (respuesta == 3) {
            int legajo, curso_index;
            cout << "\nIngrese el legajo a buscar: ";
            cin >> legajo;

            cout << "\nSeleccione el curso para buscar:\n";
            for (size_t i = 0; i < materia.size(); i++) {
                cout << i + 1 << ". " << materia[i].obtener_nombre() << endl;
            }
            cout << "\nIngrese el número del curso: ";
            cin >> curso_index;

            if (curso_index < 1 || curso_index > materia.size()) {
                cout << "\nCurso no válido.\n";
                continue;
            }

            if (materia[curso_index - 1].buscar_legajo(legajo)) {
                cout << "\nEl estudiante está inscrito en " << materia[curso_index - 1].obtener_nombre() << ".\n";
            } else {
                cout << "\nEl estudiante no está inscrito en el curso seleccionado.\n";
            }
        }

        else if (respuesta == 4) {
            int curso_index;
            cout<<"\nSeleccione el curso:\n";
            for (size_t i=0; i<materia.size();i++){
                cout<<i+1<<". "<<materia[i].obtener_nombre()<<endl;
            }
            cout<<"\nIngrese el número del curso:";
            cin>>curso_index;
            
            if(curso_index-1||curso_index>materia.size()){
                cout<<"\nCurso no válido.\n";
                continue;
            }

            if (materia[curso_index-1].curso_completo()) {
                cout << "\nEl curso está completo.\n";
            } else {
                cout << "\nEl curso tiene vacantes disponibles.\n";
            }
        }

        // else if (respuesta == 5) {
        //     int curso_index;
        //     materia.ordenar_estudiantes();
        //     cout << "\nEstudiantes ordenados alfabeticamente.\n";
        // }

        // else if(respuesta==6){
        //     materia.imprimir_estudiantes();
        // }

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