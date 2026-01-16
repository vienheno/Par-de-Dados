#include <iostream>
#include <string>
#include <iomanip>
#include <random>

using namespace std;

void titulo(); //Título del proyecto
void final(); //Fin del programa

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    titulo();

    



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