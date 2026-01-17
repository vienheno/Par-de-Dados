#include <iostream>
#include <string>
#include <iomanip>
#include <random>
#include <vector>

using namespace std;

void titulo(); //Título del proyecto
void final(); //Fin del programa
void estadisticas (int cantidad, vector<int> lanzamiento_n, vector<int> primerDado, vector<int> segundoDado, vector<int> sumaDados);
void lanzarDados(int cantidad, vector<int> lanzamiento_n, vector<int> primerDado, vector<int> segundoDado, vector<int> sumaDados);
bool nuevoLanzamiento();
void validacion(int cantidad);


struct lanzamientoDados
{
    vector<int> i_lanzamiento;
    vector<int> dado1;
    vector<int> dado2;
    vector<int> suma;
};


int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    srand(time(0));
    titulo();

    int cantidad;
    lanzamientoDados lanzar;

    //do {
        cout << "Cantidad de lanzamientos: ";
        cin >> cantidad;

        validacion (cantidad);

        lanzarDados(cantidad, lanzar.i_lanzamiento, lanzar.dado1, lanzar.dado2, lanzar.suma);
    //} while (nuevoLanzamiento());


    final();
    return 0;
}

void titulo() {
    system("cls");
    cout << "--------------- Lanzamiento de Dados -----------------" << endl;
}

void final() {
    cout << endl << endl << "--------------------- Gracias ------------------------" << endl << endl;
}

void estadisticas (int cantidad, vector<int> lanzamiento_n, vector<int> primerDado, vector<int> segundoDado, vector<int> sumaDados) {
    cout<<left<<setw(10)<<"lanzamientos:  ";
    for (int n : lanzamiento_n) {
        cout<<left<<setw(10)<<n;
    }

    cout<<endl<<left<<setw(15)<<"Dado 1:  ";
    for (int n : primerDado) {
        cout<<left<<setw(10)<<n;
    }

    cout<<endl<<left<<setw(15)<<"Dado 2:  ";
    for (int n : segundoDado) {
        cout<<left<<setw(10)<<n;
    }

    cout<<endl<<left<<setw(15)<<"Suma:  ";
    for (int n : sumaDados) {
        cout<<left<<setw(10)<<n;
    }
}

void lanzarDados(int cantidad, vector<int> lanzamiento_n, vector<int> primerDado, vector<int> segundoDado, vector<int> sumaDados){
    for (int i=0; i<cantidad; i++){
        lanzamiento_n.push_back(i+1);
        primerDado.push_back(rand() % 6 + 1);
        segundoDado.push_back(rand() % 6 + 1);
        sumaDados.push_back(primerDado[i] + segundoDado[i]);
    }

    estadisticas (cantidad, lanzamiento_n, primerDado, segundoDado, sumaDados);
}

void validacion (int cantidad){
    while(cantidad<1||cin.fail()){
        cin.clear();         
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa un número a partir del 1 para jugar." << endl;
        cin >> cantidad;
    }
}

    /*

bool nuevoLanzamiento(){
    int opcion;
    cout << "¿Quieres volver a jugar?\n1.- Sí\t0.- No" << endl;
    cin >> opcion;
    while (opcion!=1 && opcion!=0 || cin.fail()){
        cin.clear();         
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa una opción válida\n1.- Sí\t0.- No" << endl;
        cin >> opcion;
    }
    return opcion;
}
    */