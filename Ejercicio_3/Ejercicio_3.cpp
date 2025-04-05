#include <iostream>
#include <string>
#include <memory>
#include <sstream>

using namespace std;

class Numero{
    public:
        virtual shared_ptr<Numero> suma(const shared_ptr<Numero>& num) const=0; //establezco metodos puros virtuales
        virtual shared_ptr<Numero> resta(const shared_ptr<Numero>& num) const=0;
        virtual shared_ptr<Numero> producto(const shared_ptr<Numero>& num) const=0;
        virtual string toString() const = 0 ; //devuelve un numero en formato string en consol
        virtual ~Numero()=default; //destructor default
};

class Real : public Numero{
    private:
        float valor;
    public:
        Real(float v):valor(v){} //constructor real

        float get_valor()const{
            return valor;
        }

        shared_ptr<Numero> suma(const shared_ptr<Numero>& num) const override{
            if(auto real2 = dynamic_pointer_cast<Real>(num)){ //dynamic_pointer_cast verifica si el otro num es del type correcto.
                float resultado = valor + real2->valor;
                return make_shared<Real>(resultado);
            }
            throw invalid_argument("Número insertado es incompatible para suma con Reales.");
        }

        shared_ptr<Numero> resta(const shared_ptr<Numero>& num) const override{
            if(auto real2 = dynamic_pointer_cast<Real>(num)){
                float resultado = valor - real2->valor;
                return make_shared<Real>(resultado);
            }
            throw invalid_argument("Número insertado es incompatible para resta con Reales.");
        }

        shared_ptr<Numero> producto(const shared_ptr<Numero>& num) const override{
            if(auto real2 = dynamic_pointer_cast<Real>(num)){
                float resultado = valor*real2->valor;
                return make_shared<Real>(resultado);
            }
            throw invalid_argument("Número insertado es incompatible para producto entre Reales.");
        }

        string toString() const override {
            ostringstream oss;
            oss.precision(2);
            oss << fixed << valor;
            return oss.str();
        }
};

class Complejo : public Numero{
    private:
        float real, imaginaria;
    public:
        Complejo(float r, float i):real(r),imaginaria(i){} //constructor complejo

        float get_valor_real()const{
            return real;
        }

        float get_valor_img()const{
            return imaginaria;
        }

        shared_ptr<Numero> suma (const shared_ptr<Numero>& num) const override{
            if(auto complejo2 = dynamic_pointer_cast<Complejo>(num)){
                float resultado_real = real + complejo2->real;
                float resultado_img = imaginaria + complejo2->imaginaria;
                return make_shared<Complejo>(resultado_real, resultado_img);
            }
            throw invalid_argument("El número insertado es incompatible para suma de Complejos.");
        }

        shared_ptr<Numero> resta (const shared_ptr<Numero>& num) const override{
            if(auto complejo2 = dynamic_pointer_cast<Complejo>(num)){
                float resultado_real = real - complejo2->real;
                float resultado_img = imaginaria - complejo2->imaginaria;
                return make_shared<Complejo>(resultado_real, resultado_img);
            }
            throw invalid_argument("El número insertado es incompatible para restar con Complejos.");
        }
        shared_ptr<Numero> producto (const shared_ptr<Numero>& num) const override{
            if(auto complejo2=dynamic_pointer_cast<Complejo>(num)){
                float a = real;
                float b = imaginaria;
                float c = complejo2->real;
                float d = complejo2->imaginaria;

                float resultado_real = (a*c) -(b* d);
                float resultado_imaginaria = (a *d)+ (b *c);

                return make_shared<Complejo>(resultado_real, resultado_imaginaria);
            }
            throw invalid_argument("El número insertado es incompatible para el producto entre Complejos.");
        }

        string toString() const override{
            ostringstream oss;
            oss.precision(2);
            oss << fixed;
            
            if (real == 0 && imaginaria == 0){
                return "0";
            }

            else if (imaginaria == 0){
                oss << real;
                return oss.str();
            }

            else if (real == 0){
                oss << imaginaria << "i";
                return oss.str();
            }

            else{ //si imaginaria es >= 0 devolvé + sino devolvé -
                oss << real << (imaginaria >= 0 ? " + " : " - ") << abs(imaginaria) << "i";
                return oss.str();            
            }
        }
};

class Entero : public Numero{
    private:
        int valor;
    public:
        Entero(int v):valor(v){} //constructor de entero

        int get_valor()const{
            return valor;
        }

        shared_ptr<Numero> suma(const shared_ptr<Numero>& num) const override{
            if (auto entero2 = dynamic_pointer_cast<Entero>(num)){
                int resultado=valor+entero2->valor;
                return make_shared<Entero>(resultado);
            }
            throw invalid_argument("Número insertado es incompatible para sumar con Enteros.");
        }

        shared_ptr<Numero> resta(const shared_ptr<Numero>& num) const override{
            if (auto entero2 = dynamic_pointer_cast<Entero>(num)){
                int resultado=valor-entero2->valor;
                return make_shared<Entero>(resultado);
            }
            throw invalid_argument("Número insertado es incompatible para restar con Enteros.");
        }

        shared_ptr<Numero> producto(const shared_ptr<Numero>& num) const override{
            if (auto entero2=dynamic_pointer_cast<Entero>(num)){
                int resultado = valor*entero2->valor;
                return make_shared<Entero>(resultado);
            }
            throw invalid_argument("Número insertado es incompatible para producto entre Enteros.");
        }

        string toString() const override{
            return to_string(valor);
        }
};

int main() {
    try {
        // Crear objetos
        shared_ptr<Numero> e1 = make_shared<Entero>(15000);
        shared_ptr<Numero> e2 = make_shared<Entero>(10000);
        shared_ptr<Numero> e3 = make_shared<Entero>(3);
        shared_ptr<Numero> e4 = make_shared<Entero>(1000);

        shared_ptr<Numero> r1 = make_shared<Real>(2.5);
        shared_ptr<Numero> r2 = make_shared<Real>(1.5);
        shared_ptr<Numero> r3 = make_shared<Real>(173.5);
        shared_ptr<Numero> r4 = make_shared<Real>(171.5);

        shared_ptr<Numero> c1 = make_shared<Complejo>(3, 4);
        shared_ptr<Numero> c2 = make_shared<Complejo>(1, -2);

        cout << "\nOperaciones con números enteros:\n" << endl;
        cout << "Hoy pagué $15000 de la tarifa de la luz y $10000 de gas. En total gasté: $" << e1->suma(e2)->toString() << endl;
        cout << "La diferencia entre las tarifas es de: $" << e1->resta(e2)->toString() << endl;
        cout << "Compré 3 Coca-Colas por $1000 pesos cada una, gasté $" << e3->producto(e4)->toString() << " en total."<< endl;

        cout << "\nOperaciones con números reales:\n" << endl;
        cout << "De chico me costaba $2.5 una hamburguesa y $1.5 unas papas, almorzaba con solamente $" << r1->suma(r2)->toString() <<" pesos!"<< endl;
        cout << "Ahora mido 173.5cm y en 2023 medía 171.5cm, crecí " << r3->resta(r4)->toString() <<" cm."<< endl;
        cout << "Compré 2.5 kg de frutillas y vale $1.5 cada kg. Gasté $" << r1->producto(r2)->toString() << " dólares."<< endl;

        cout << "\nOperaciones con números complejos:\nEjemplo impedencias eléctricas:\n" << endl;
        cout << "Z1 = " << c1->toString() << " ohms" << endl;
        cout << "Z2 = " << c2->toString() << " ohms" << endl;
        cout << "\nImpedancia total en serie: " << c1->suma(c2)->toString() << " ohms." << endl;
        cout << "Diferencia entre impedancias: " << c1->resta(c2)->toString() << " ohms." << endl;
        cout << "Producto de impedancias: " << c1->producto(c2)->toString() << " ohms²." << endl;

        // Casos de error (intencionales)
        cout << "\nCasos intencionales de Errores por operaciones entre tipos:\n" << endl;

        try {
            // Caso: Entero + Real
            cout << "1. Entero + Real:\n15000 + 2.5";
            cout << e1->suma(r1)->toString() << endl;
        } catch (const exception& e) {
            cout << "\nExcepción capturada: " << e.what() << endl;
        }

        try {
            // Caso: Real * Complejo
            cout << "\n2. Real * Complejo:\n2.5 * (3 + 4i)";
            cout << r1->producto(c1)->toString() << endl;
        } catch (const exception& e) {
            cout << "\nExcepción capturada: " << e.what() << endl;
        }

        try {
            // Caso: Complejo - Entero
            cout << "\nComplejo - Entero:\n(3 + 4i) - 15000";
            cout << c1->resta(e1)->toString() << endl;
        } catch (const exception& e) {
            cout << "\nExcepción capturada: " << e.what() << endl;
        }

    } catch (const exception& e) {
        cerr << "\nError general: " << e.what() << endl;
    }

    return 0;
}
