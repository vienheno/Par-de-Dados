#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

struct lanzamientoDeDados
{
    int lanzamientos;
    int dado1;
    int dado2;
    int sumaTotal;
};

void titulo(); 

void lanzarDados(lanzamientoDeDados *simulacion, int lanzamientos);
void guardarEnArchivo(lanzamientoDeDados *simulacion, int lanzamientos);
void estadisticas();
void partidaNueva();

int contarLanzamientosPrevios();

void validacion(int &lanzamientos);
void validacionMenu (int &opc);

void final();

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    srand(time(0));

    titulo();

    int opc;

    do {
        cout << "--------------- MENU ---------------"<<endl;
        cout << "1. Lanzamiento(s)"<<endl;
        cout << "2. Partida nueva"<<endl;
        cout << "3. Ver estadisticas"<<endl;
        cout << "4. Salir"<<endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        cout << "-----------------------------------"<<endl;

        validacionMenu (opc);

        switch (opc) {
        case 1:{
            int lanzamientos;
            cout << "Cantidad de lanzamientos: ";
            cin >> lanzamientos;

            validacion (lanzamientos);

            lanzamientoDeDados *simulacion = new lanzamientoDeDados[lanzamientos];

            lanzarDados(simulacion, lanzamientos);
            guardarEnArchivo(simulacion, lanzamientos);

            delete[] simulacion;

            break;
        }

        case 2:

            partidaNueva();
            break;

        case 3:

            estadisticas();
            break;
        }

    } while (opc!=4);

    final();

    return 0;
}

void titulo() {
    system("cls");
    cout << "------- Lanzamiento de Dados -------" << endl;
}

void lanzarDados(lanzamientoDeDados *simulacion, int lanzamientos){
    
    for (int i=0; i<lanzamientos; i++){
        simulacion[i].lanzamientos = i+1;
        simulacion[i].dado1 = rand() % 6 + 1;
        simulacion[i].dado2 = rand() % 6 + 1;
        simulacion[i].sumaTotal = simulacion[i].dado1 + simulacion[i].dado2;
    }
}

void guardarEnArchivo(lanzamientoDeDados *simulacion, int lanzamientos){
    int lanzamientosPrevios = contarLanzamientosPrevios();

    ofstream archivo("resultados_dados.txt", ios::app);

    if(!archivo){
        cout << "Error al crear el archivo." << endl;
        return;
    }

    if (lanzamientosPrevios == 0) {
        archivo << left 
                << setw(12) << "No."
                << setw(12) << "Dado1"
                << setw(12) << "Dado2"
                << setw(12) << "Total" 
                << endl;
    }

    for (int i=0; i<lanzamientos; i++){
        archivo << left
                << setw(12) << simulacion[i].lanzamientos
                << setw(12) << simulacion[i].dado1
                << setw(12) << simulacion[i].dado2
                << setw(12) << simulacion[i].sumaTotal
                <<endl;
    }

    archivo.close();
}

void estadisticas(){
    ifstream archivo("resultados_dados.txt");

    int contador[13] = {0};

    if (!archivo) {
        cout << "No hay datos registrados." << endl;
        return;
    }

    string linea;
    getline(archivo, linea);

    int num, d1, d2, suma;

    while (archivo >> num >> d1 >> d2 >> suma) {
        contador[suma]++;
    }

    archivo.close();

    cout << "----- Estadísticas Acumuladas -----" << endl;
    cout << fixed << setprecision(2);

    if (contarLanzamientosPrevios() == 0) {
        cout << "No hay lanzamientos registrados." << endl;
        return;
    }

    for (int i = 2; i <= 12; i++) {
        double porcentaje = (contador[i] * 100.0) / contarLanzamientosPrevios();
        cout << i << ": " << porcentaje << "%" << endl;
    }
}

void partidaNueva(){
    ofstream archivo("resultados_dados.txt");

    if (!archivo) {
        cout << "Error al reiniciar la partida." << endl;
        return;
    }

    archivo.close();

    cout << "Partida nueva iniciada. Historial borrado." << endl;

}

int contarLanzamientosPrevios(){
    ifstream archivo("resultados_dados.txt");

    int contador = 0;
    string linea;

    if (!archivo)
        return 0;

    getline(archivo, linea);

    while (getline(archivo, linea)) {
        contador++;
    }

    archivo.close();
    return contador;
}

void validacion (int &lanzamientos){
    while(lanzamientos<1||cin.fail()){
        cin.clear();         
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa un número a partir del 1 para jugar." << endl;
        cin >> lanzamientos;
    }
}

void validacionMenu (int &opc){
    while(opc<1||opc>4||cin.fail()){
        cin.clear();         
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa una opción válida del menú." << endl;
        cin >> opc;
    }
}

void final() {
    cout << endl << endl << "------------- Gracias -------------" << endl << endl;
}