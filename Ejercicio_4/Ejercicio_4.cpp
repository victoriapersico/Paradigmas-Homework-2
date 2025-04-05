#include <iostream>
#include <string>
#include <memory>

using namespace std;

class Cuenta{
    private:
        double balance; //balance y titularCuenta: son private porque no se permite su acceso, solo lós métodos o desde dentro de Curso se pueden modificar y acceder a ellos. 
        string titularCuenta; //que sean private evita errores como modificaciones del nombre del titular de una cuenta o saldos negativos.

    public:
        Cuenta(string titular, double saldo_inicial):titularCuenta(titular),balance(saldo_inicial){}
        
        virtual ~Cuenta()=default; //destructor: es public porque se accede desde afuera
        
        virtual double retirar(double monto)=0; //retirar: public porque tiene que poder accederse desde afuera. no es const porque modifica un atributo del obj
       
        virtual void mostrarInfo() =0; //mostrarInfo: es public porque el user tiene que poder acceder para ver la info de la cuenta, no se usa const porque modifica el estado del obj, el contador y el balance
        
        void depositar(double saldo){
            balance+=saldo; //depositar es public para que el usuario pueda usarlo desde afuera, y modifica balance, por eso no es const.
        }

        double get_balance_privado(){
            return get_balance();
        }

    protected: //son los setters y getters, las subclases pueden acceder a valores private sin romper encapsulación
        double get_balance() const{ //const ya que no modifica al obj
            return balance;
        }
        void set_balance(double nuevo_balance){
            balance=nuevo_balance;
        }
        string get_titularCuenta() const{
            return titularCuenta;
        }
};

class CuentaCorriente; //forward declaration

class CajaDeAhorro : public Cuenta {
    private:
        mutable int contador_accesos =0; //mantiene un conteo de la cantidad de veces que se muestra info cuenta, es un mutable así se puede modificar en el método const mostrarInfo()
        friend class CuentaCorriente;
    public:
        CajaDeAhorro(string titular, double saldo_inicial):Cuenta(titular, saldo_inicial){} //constructor, lista inicializacion

        double retirar(double monto) override{
            if (monto>get_balance()){
                throw invalid_argument("El monto a retirar no puede ser mayor que su balance.");
            }
            set_balance(get_balance()-monto);
            return monto;
        }

        void mostrarInfo() override{
            cout<<"\nCuenta: Caja de Ahorro.\n"<<endl;
            cout<<"Titular: "<<get_titularCuenta()<<"."<<endl;
            cout<<"\nBalance: C$"<<get_balance()<<" dólares canadienses."<<endl;
            contador_accesos++;
            if (contador_accesos>2){
                set_balance(get_balance()- 20);
                cout<<"Se descontaron C$20 ya que alcanzaste el límite de 2 visualizaciones de información de cuenta gratuitas."<<endl;
            }
        }
};

class CuentaCorriente : public Cuenta{
    private:
        shared_ptr<CajaDeAhorro> caja_ahorro_usuario;
    public:
        CuentaCorriente(string titular, double saldo_corriente, shared_ptr<CajaDeAhorro>caja):Cuenta(titular, saldo_corriente), caja_ahorro_usuario(caja){}

        double retirar(double monto) override{
            if(monto<=get_balance()){
                set_balance(get_balance()-monto);
                return monto;
            }
            else{
                double monto_restante = monto - get_balance();
                if (caja_ahorro_usuario->get_balance_privado() >= monto_restante){ 
                    double saldo_ahorro_utilizado = caja_ahorro_usuario->retirar(monto_restante); //CajadeAhorro::retirar() se encarga de descontar el saldo tomado de ahí
                    set_balance(0);
                    return get_balance() + saldo_ahorro_utilizado; //devuelvo todo el saldo de la CuentaCorriente + el tomado de la CajaDeAhorro
                }
                else{
                    cout<<"No exiten fondos suficientes para la extracción deseada ni en su Caja de Ahorro ni en su Cuenta Corriente."<<endl;
                    return 0;
                }
            }
        }

        void mostrarInfo() override{
            cout<<"\nCuenta: Cuenta Corriente.\n"<<endl;
            cout<<"Titular: "<<get_titularCuenta()<<"."<<endl;
            cout<<"\nBalance: C$"<<get_balance()<<" dólares canadienses."<<endl;
        }
};

//como declaro CuentaCorriente como friend de CajaDeAhorro puedo acceder desde CuentaCorriente a su metodo privado
// get_balance_privado() que me permite acceder al balance de la caja de ahorro, que es un atributo privado heredado de la clase base Cuenta
// y así no tengo que definir getters publicos. 

int main() {
    auto caja_ahorro = make_shared<CajaDeAhorro>("Victoria Pérsico", 1000);
    CuentaCorriente cuenta_corriente("Victoria Pérsico", 500, caja_ahorro);

    cuenta_corriente.mostrarInfo();
    caja_ahorro->mostrarInfo();

    cout << "\n1. OPERACION: retirar C$800 desde su cuenta corriente.\n";
    cuenta_corriente.retirar(800);

    cuenta_corriente.mostrarInfo();
    caja_ahorro->mostrarInfo();

    cout << "\n2. OPERACION: retirar C$2000 desde su cuenta corriente.\n";
    cuenta_corriente.retirar(2000);

    return 0;
}