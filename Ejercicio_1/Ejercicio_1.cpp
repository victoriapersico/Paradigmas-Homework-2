#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class Clock {
    private:
        int HH, MM, SS;
        string meridiem_indicator;

    public:
        // constructor con params default
        Clock(int HH=0, int MM=0, int SS=0, const string& meridiem_indicator="a.m.") : HH(HH), MM(MM), SS(SS), meridiem_indicator(meridiem_indicator){
            set_hour(HH);
            set_minute(MM);
            set_second(SS);
            set_meridiem(meridiem_indicator);
        }
    void show_time (){
        cout << setfill('0') << setw(2)<<HH<<"h, "<< setw(2)<<MM<<"m, "<<setw(2)<<SS<<"s "<<meridiem_indicator<<"\n";
    }

    void military_time(){
        int military_HH = HH;
        if (meridiem_indicator=="a.m." && HH==12){
            military_HH=0; //caso 12 am = 00hs
        }
        else if(meridiem_indicator=="p.m." && HH!=12){
            military_HH+=12;

        }
        cout<<setfill('0')<<setw(2)<<military_HH<<" hs., "<< setw(2)<<MM<<" minutes, "<<setw(2)<<SS<<" seconds.";
    }
    void set_hour(int hour_time){
        if (hour_time<0 || hour_time> 12){
            throw invalid_argument("Error: Invalid argument. Hour time should be between 12 and 1.");
        }
        HH=hour_time;
    }
    int get_hour(){
        return HH;
    }

    void set_minute(int minute_time){
        if (minute_time<0 || minute_time>59){
            throw invalid_argument("Error: Invalid argument. Minute time should be between 59 and 0.");
        }
        MM=minute_time;
    }
    int get_minute(){
        return MM;
    }
    void set_second(int second_time){
        if (second_time<0 || second_time>59){
            throw invalid_argument("Error: Invalid argument. Second time should be between 59 and 0.");
        }
        SS=second_time;
    }
    int get_second(){
        return SS;
    }
    void set_meridiem(const string& meridiem){
        if (meridiem != "a.m." && meridiem != "p.m."){
            throw invalid_argument("Error: Invalid argument. A meridiem indicator is either 'a.m.' or 'p.m.'.");
        }
        meridiem_indicator=meridiem;
    }
    string get_meridiem() { 
        return meridiem_indicator; 
    }
};


int main() {
    int HH = 0, MM = 0, SS = 0;
    string meridiem = "a.m.";

    //Función extra para manejar los casos que el usuario quiere salir del programa.
    auto retry_or_exit = []() {
        string retry;
        cout << "Do you want to try again? (YES/NO): ";
        cin >> retry;
        if (retry == "NO" || retry == "no" || retry == "No") {
            cout << "Ending program.\n";
            return false;
        }
        return true;
    };

    try {
        cout << "\nA. No arguments:\n";
        Clock clock1;
        clock1.show_time();
    } catch (const exception& e) {
        cout << e.what() << endl;
    }

    while (true) {
        try {
            cout << "\nB. Initializing hour time: \nInsert hour time in civilian time: ";
            cin >> HH;
            Clock clock2(HH);
            clock2.show_time();
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
            if (!retry_or_exit()) return 1;
        }
    }

    while (true) {
        try {
            cout << "\nC. Initializing minute time: \nInsert minute time: ";
            cin >> MM;
            Clock clock3(HH, MM);
            clock3.show_time();
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
            if (!retry_or_exit()) return 1;
        }
    }

    while (true) {
        try {
            cout << "\nD. Initializing second time: \nInsert second time: ";
            cin >> SS;
            Clock clock4(HH, MM, SS);
            clock4.show_time();
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
            if (!retry_or_exit()) return 1;
        }
    }

    while (true) {
        try {
            cout << "\nE. Initializing the meridiem indicator: \nInsert the meridiem indicator: ";
            cin >> meridiem;
            Clock clock5(HH, MM, SS, meridiem);
            clock5.show_time();
            break;
        } catch (const exception& e) {
            cout << e.what() << endl;
            if (!retry_or_exit()) return 1;
        }
    }
    while (true){
        try{
            Clock clock6(HH,MM,SS,meridiem);
            cout<< "\nF. Modifying and showing values individually:\nStarting time: ";
            clock6.show_time();

            cout<<"\nHour time before: "<<clock6.get_hour();
            cout<<"\nModifying hour time to 10.\nModified time: ";
            clock6.set_hour(10);
            clock6.show_time();

            cout<<"\nMinute time before: "<<clock6.get_minute();
            cout<<"\nModifying minute time to 11.\nModified time: ";
            clock6.set_minute(11);
            clock6.show_time();

            cout<<"\nSecond time before: "<<clock6.get_second();
            cout<<"\nModifying second time to 12.\nModified time: ";
            clock6.set_second(12);
            clock6.show_time();

            cout<<"\nMeridiem indicator before: "<<clock6.get_meridiem();
            cout<<"\nModifying meridiem indicator to 'p.m.'.\nModified time: ";
            clock6.set_meridiem("p.m.");
            clock6.show_time();

            HH = clock6.get_hour();
            MM = clock6.get_minute();
            SS = clock6.get_second();
            meridiem = clock6.get_meridiem();
            break;
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            if (!retry_or_exit()) return 1;
        }
    }
    while(true){
        try{
            Clock clock7(HH,MM,SS,meridiem);
            cout << "\nH. Military time:\nTime in civilian time: ";
            clock7.show_time();
            cout << "\nTime in military time: ";
            clock7.military_time();
            cout << endl;
            break;
        }
        catch(const exception& e){
            cout<<e.what()<<endl;
            if(!retry_or_exit()) return 1;
        }
    }
    return 0;
}
