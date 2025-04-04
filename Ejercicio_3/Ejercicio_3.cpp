#include <iostream>
#include <string>
#include <memory>

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

        string toString() const override{
            return to_string(valor);
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
            if (real == 0 && imaginaria == 0){
                return "0";
            }
            else if (imaginaria == 0){
                return to_string(real);
            }
            else if (real == 0){
                return to_string(imaginaria) + "i";
            }
            else{ //si imaginaria es >= 0 devolvé + sino devolvé -
                return to_string(real) + (imaginaria >= 0 ? " + " : " - ") + to_string(abs(imaginaria)) + "i";
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

