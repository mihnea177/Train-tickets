#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <regex>
using namespace std;

const regex pattern("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d).+$");
string TheAccount;
int status;

class Account{
    public:
    string username;
    string password;
    void AccountCreate(){
        int ok = 0;
        system("clear");
        do{
            cout << "EMAIL (exemplu@email.com): "; cin >> username;
            try{
                if(username.find('@')<username.length())
                    ok = 1/2;
                else
                    throw 99999;
                if(username.find(".com")<username.length())
                    ok = 1;
                else
                    throw 99999;
            }
            catch(int err){
                cerr << "EMAIL INTRODUS GRESIT" << "\n\n";
            }
        }while(ok==0);

        system("clear");
        ok = 0;
        string aux;

        do{
            cout << "PAROLA (trebuie sa contina minim o litera mica, o litera mare si o cifra): ";
            cin >> password;
            try{
                if(regex_match(password, pattern))
                    ok = 1;
                else
                    throw 99999;
            }
            catch(int err){
                cerr << "PAROLA PREA SLABA" << "\n\n";
            }
        }while(ok == 0);

        system("clear");
        ok = 0;

        do{
            cout << "REPETATI PAROLA: ";
            cin >> aux;
            try{
                if(aux == password)
                    ok = 1;
                else
                    throw 99999;
            }
            catch(int err){
                cerr << "PAROLELE NU COINCID" << "\n\n";
            }
        }while(ok == 0);
        
        ofstream f;
        f.open("accounts.csv", ios::app);
        f << username << ',' << password << ',' << '\n';
        f.close();
    }


};

void CreateAccount(){
    Account acc;
    acc.AccountCreate();
}

void AccesAccount(){
    ifstream f;
    f.open("accounts.csv");
    try{
        if(!f)
            throw 99999;
    }
    catch(int err){
        cerr << "NU SE POATE ACCESA BAZA DE DATE A CONTURILOR" << endl;
    }

    string line;
    string GivenUsername, GivenPass;
    string CheckUsername, CheckPass;
    float ok = 0;
    string delimiter = ",";
    size_t pos = 0;

    cout << "Email: "; cin >> GivenUsername;
    cout << endl;
    cout << "Parola: "; cin >> GivenPass;
    system("clear");
    ok = 0;
    while(getline(f,line)){
        if((pos = line.find(delimiter)) != string::npos){
            CheckUsername = line.substr(0,pos);
            if (CheckUsername == GivenUsername)
                ok++;
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            CheckPass = line.substr(0,pos);
            if (CheckPass == GivenPass)
                ok++;
            line.erase(0, pos+delimiter.length());
       }
    }
    if(ok == 2) {
        TheAccount = GivenUsername;
        status = 1;
    }
    else
        status = 0;
    f.close();
}

void SearchRoute(){
    int option;
    string GivenStart, GivenDestination, GivenDate;
    system("clear");
    cout << "INTRODUCETI PUNCTUL DE PLECARE: "; cin >> GivenStart;
    cout << endl << endl << "INTRODUCETI DESTINATIA: "; cin >> GivenDestination;
    cout << endl << endl << "INTRODUCETI DATA (ex: 10.06.2022): "; cin >> GivenDate;
    ifstream f;
    f.open("trains.csv");
    try{
        if(!f)
            throw 99999;
    }
    catch(int err){
        cerr << "NU SE POATE ACCESA BAZA DE DATE A CALATORIILOR" << endl;
    }

    const regex pattern2("^(?=.*[0-9]).+$");

    try{
        if (regex_match(GivenStart, pattern2))
            throw 99999;
        if(regex_match(GivenDestination, pattern2))
            throw 99999;
    }catch(int err){
        cerr << "PUNCTUL DE PLECARE SAU DESTINATIA ESTE SCRIS GRESIT" << endl;
    }

    string delimiter = ",";
    size_t pos = 0;
    string line;
    string CheckStart, CheckDestination, CheckDate, TrainTime, TrainID;
    int ok = 0;
    int found = 0;
    system("clear");

    while(getline(f,line)){
        ok = 0;
        if((pos = line.find(delimiter)) != string::npos){
            CheckStart = line.substr(0,pos);
            if (CheckStart == GivenStart)
                ok++;
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            CheckDestination = line.substr(0,pos);
            if (CheckDestination == GivenDestination)
                ok++;
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            CheckDate = line.substr(0,pos);
            if (CheckDate == GivenDate)
                ok++;
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            TrainTime = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            TrainID = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        if(ok == 3){
            found++;
            cout << "CALATORIA  " << found;
            cout << endl << "------------------" << endl;
            cout << "PUNCT DE PLECARE: " << CheckStart << endl;
            cout << "PUNCT DE SOSIRE: " << CheckDestination << endl;
            cout << "DATA: " << CheckDate << endl;
            cout << "ORA DE PLECARE: " << TrainTime << endl;
            cout << "NUMARUL TRENULUI (PENTRU REZERVARE BILET): " << TrainID << endl;
            cout << "----------------------------------------------------------------" << endl << endl;
        }
    }
    try{
        if(found == 0)
            throw 99999;
        else{
            system("read");
            system("clear");
        }
    }
    catch(int err){
        cerr << "NU EXISTA O CALATORIE CARE SA CORESPUNDA CRITERIILOR DVS" << endl;
    }
    f.close();
}

void BookRoute(){
    string GivenTrainID;
    system("clear");
    cout << "INTRODUCETI NUMARUL TRENULUI: "; cin >> GivenTrainID;
    ifstream f;
    f.open("trains.csv");
    try{
        if(!f)
            throw 99999;
    }
    catch(int err){
        cerr << "NU SE POATE ACCESA BAZA DE DATE A CALATORIILOR";
    }
    string st,dt,da,tm,TrainID;
    string line;
    int ok = 0;
    size_t pos = 0;
    string delimiter = ",";
    string choice;
    int check;

    while(getline(f,line)){
        ok = 0;
        if((pos = line.find(delimiter)) != string::npos){
            st = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            dt = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            da = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            tm = line.substr(0,pos);
            line.erase(0, pos+delimiter.length());
        }
        if((pos = line.find(delimiter)) != string::npos){
            TrainID = line.substr(0,pos);
            if (TrainID == GivenTrainID)
                ok++;
            line.erase(0, pos+delimiter.length());
        }
        if(ok == 1){
            cout << endl;
            cout << "DORITI SA REZERVATI UN BILET PENTRU URMATOAREA CALATORIE ? " << endl << endl;
            cout << "PUNCT DE PLECARE: " << st << endl;
            cout << "PUNCT DE SOSIRE: " << dt << endl;
            cout << "DATA: " << da << endl;
            cout << "ORA DE PLECARE: " << tm << endl;
            cout << "----------------------------------------------------------------" << endl << endl;
            do{
                cout << "TASTATI DA SAU NU: "; 
                cin >> choice;
                if(choice == "DA") check = 1;
                if(choice == "NU") check = 2;
            }while(check < 1);
            break;
        }
    }
    try{
        if(ok == 0) throw 9999;
    }
    catch(int err){
        cerr << "NU A FOST GASIT UN TREN CU ACEST NUMAR";
    }

    cout << endl;
    if (choice == "NU"){
        cout << "ATI ANULAT REZERVAREA TRENULUI"<< endl << endl;
    }

    string nume, prenume;
    if (choice == "DA"){
        system("clear");
        cout << "NUME: "; cin >> nume; cout << endl;
        system("clear");
        cout << "PRENUME: "; cin >> prenume; cout << endl;
        system("clear");
        cout << "ATI REZERVAT UN BILET PE NUMELE " << endl << endl;
        cout << nume << ' ' << prenume << endl << endl;
        cout << "PENTRU CALATORIA: " << endl << endl;
        cout << st << '-' << dt << " DIN DATA: " << da << " ORA: " << tm << endl;
    }
    system("read");
    system("clear");
}

int main(){
    int option;
    int runs = 5;

    do{
        system("clear");
        cout << endl << endl;
        cout << "APLICATIE PENTRU CAUTAREA SI REZERVAREA CALATORIILOR CU TRENUL \n\n";
        cout << "1. CREARE CONT \n";
        cout << "2. AUTENTIFICARE \n";
        cout << "3. INCHIDERE \n\n";
        cout << "ALEGETI OPTIUNEA: ";
        cin >> option;
        switch(option){
            case 1:
                system("clear");
                CreateAccount();
                cout << "----CONT CREAT---- \n";
                system("read");
                break;
            case 2:
                system("clear");
                
                do{
                    runs--;
                    cout << runs << " INCERCARI DE LOGIN RAMASE \n";
                    cout << "-----------------------------------" << endl;
                    if (runs == 0) status = 1;
                    AccesAccount();
                }while(status != 1);
                system("clear");
                break;
            case 3:
                system ("clear");
                status = 2;
                cout << "Aplicatie inchisa \n\n";
                break;
            default: break;
        }
    }while(status < 1);

    do{
        if (status == 2 || status == 0) break;
        if(status == 1){
            cout << "AUTENTIFICAT CA: " << TheAccount << endl;
            cout << "----------------------------------------" << endl << endl;
        }
        cout << "1. CAUTARE CURSA" << endl;
        cout << "2. REZERVARE CURSA" << endl;
        cout << "3. INCHIDERE" << endl << endl;
        cout << "ALEGETI OPTIUNEA: "; cin >> option;
        switch (option){
        case 1:
            system("clear");
            SearchRoute();
            break;
        case 2:
            BookRoute();
            break;
        case 3:
            break;
        default:
            break;
        }

    }while(option!=3);
}