#include <iostream>
#include <string>
#include <iomanip>
#include <random>

using namespace std;

void titulo(); //Título del proyecto
void final(); //Fin del programa
void lanzarDados(int cantidad);
bool nuevoLanzamiento();
void validacion(int cantidad);


struct lanzamientoDados
{
    int cantidad;
    int dado1;
    int dado2;
    int suma;
};


int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    srand(time(0));

    titulo();

    int cantidad;

    do {
        cout << "Cantidad de lanzamientos: ";
        cin >> cantidad;

        validacion (cantidad);

        lanzarDados(cantidad);
    } while (nuevoLanzamiento());


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

void lanzarDados(int cantidad){
    int dado1, dado2;
    float suma2=0, suma3=0, suma4=0, suma5=0, suma6=0, suma7=0, suma8=0, suma9=0, suma10=0, suma11=0, suma12=0;
    lanzamientoDados lanzar[cantidad];
    
    for (int i=0; i<cantidad; i++){
        lanzar[i].dado1 = rand() % 6 + 1;
        lanzar[i].dado2 = rand() % 6 + 1;
        lanzar[i].suma = lanzar[i].dado1 + lanzar[i].dado2;

        switch (lanzar[i].suma){
            case 2: suma2++; break;
            case 3: suma3++; break;
            case 4: suma4++; break;
            case 5: suma5++; break;
            case 6: suma6++; break;
            case 7: suma7++; break;
            case 8: suma8++; break;
            case 9: suma9++; break;
            case 10: suma10++; break;
            case 11: suma11++; break;
            case 12: suma12++; break;
        }
    }

    cout<<"\n---------------  Estadísticas Finales ---------------"<<endl;

    cout<<"El número 2 salió "<< suma2 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma2*100.0)/cantidad << "%" <<endl;

    cout<<"El número 3 salió "<< suma3 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma3*100.0)/cantidad << "%" <<endl;

    cout<<"El número 4 salió "<< suma4 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma4*100.0)/cantidad << "%" <<endl;

    cout<<"El número 5 salió "<< suma5 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma5*100.0)/cantidad << "%" <<endl;

    cout<<"El número 6 salió "<< suma6 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma6*100.0)/cantidad << "%" <<endl;

    cout<<"El número 7 salió "<< suma7 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma7*100.0)/cantidad << "%" <<endl;

    cout<<"El número 8 salió "<< suma8 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma8*100.0)/cantidad << "%" <<endl;

    cout<<"El número 9 salió "<< suma9 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma9*100.0)/cantidad << "%" <<endl;

    cout<<"El número 10 salió "<< suma10 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma10*100.0)/cantidad << "%" <<endl;

    cout<<"El número 11 salió "<< suma11 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma11*100.0)/cantidad << "%" <<endl;

    cout<<"El número 12 salió "<< suma12 << " veces."<<endl;
    cout<<"Pocentaje de aparición: " << (suma12*100.0)/cantidad << "%" <<endl;
}

void validacion (int cantidad){
    while(cantidad<1||cin.fail()){
        cin.clear();         
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa un número a partir del 1 para jugar." << endl;
        cin >> cantidad;
    }
}

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