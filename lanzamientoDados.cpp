#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <sstream>

using namespace std;

struct lanzamientoDeDados
{
    int lanzamientos;
    int dado1;
    int dado2;
    int sumaTotal;
};
enum OpcionMenu
{
    JUGAR = 1,
    PARTIDA_NUEVA = 2,
    ESTADISTICAS = 3,
    SALIR = 4
};

void titulo();

void lanzarDados(lanzamientoDeDados *simulacion, int lanzamientos);
void mostrarResultados(lanzamientoDeDados *simulacion, int lanzamientos);
void guardarEnArchivo(lanzamientoDeDados *simulacion, int lanzamientos);
void mostrarEstadisticas(int contador[], int totalLanzamientos);
void estadisticas();
void partidaNueva();
int contarLanzamientosPrevios();
void pausar();
void validacion(int &lanzamientos);
void validacionMenu(int &opc);

void final();

int main()
{
    setlocale(LC_ALL, "es_ES.UTF-8");

    srand(time(0));

    titulo();

    int opc;

    do
    {
        cout << "--------------- MENU ---------------" << endl;
        cout << "1. Jugar" << endl;
        cout << "2. Partida nueva" << endl;
        cout << "3. Ver estadisticas" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opc;
        validacionMenu(opc);

        switch (opc)
        {
        case JUGAR:
        {
            int lanzamientos;
            cout << "\nCantidad de lanzamientos: ";
            cin >> lanzamientos;
            validacion(lanzamientos);

            lanzamientoDeDados *simulacion = new lanzamientoDeDados[lanzamientos];
            lanzarDados(simulacion, lanzamientos);
            mostrarResultados(simulacion, lanzamientos);
            guardarEnArchivo(simulacion, lanzamientos);
            delete[] simulacion;
            pausar();
            break;
        }
        case PARTIDA_NUEVA:
            partidaNueva();
            pausar();
            break;
        case ESTADISTICAS:
            estadisticas();
            pausar();
            break;
        }

        titulo();
    } while (opc != SALIR);

    final();

    return 0;
}

void titulo()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║          SIMULADOR DE LANZAMIENTO DE DADOS         ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
    cout << "\n";
}

void lanzarDados(lanzamientoDeDados *simulacion, int lanzamientos)
{

    for (int i = 0; i < lanzamientos; i++)
    {
        simulacion[i].lanzamientos = i + 1;
        simulacion[i].dado1 = rand() % 6 + 1;
        simulacion[i].dado2 = rand() % 6 + 1;
        simulacion[i].sumaTotal = simulacion[i].dado1 + simulacion[i].dado2;
    }
}
void mostrarResultados(lanzamientoDeDados *simulacion, int lanzamientos)
{
    cout << "\nResultados del juego:\n\n";
    cout << left << setw(12) << "Lanzamiento"
         << setw(12) << "Dado 1"
         << setw(12) << "Dado 2"
         << setw(12) << "Total" << endl;
    cout << string(48, '-') << endl;

    for (int i = 0; i < lanzamientos; i++)
    {
        cout << left << setw(12) << simulacion[i].lanzamientos
             << setw(12) << simulacion[i].dado1
             << setw(12) << simulacion[i].dado2
             << setw(12) << simulacion[i].sumaTotal << endl;
    }
}

void pausar()
{
    cout << "\nPresiona ENTER para continuar...";
    cin.ignore();
    cin.get();
}
void guardarEnArchivo(lanzamientoDeDados *simulacion, int lanzamientos)
{
    int lanzamientosPrevios = contarLanzamientosPrevios();
    ofstream archivo("resultados_dados.txt", ios::app);
    if (!archivo)
    {
        cout << "Error al crear el archivo." << endl;
        return;
    }
    if (lanzamientosPrevios == 0)
    {
        archivo << "Historial de Lanzamientos de Dados" << endl;
        archivo << left << setw(10) << "Dado1" << setw(10) << "Dado2" << setw(10) << "Suma" << endl;
        archivo << string(30, '=') << endl;
    }
    for (int i = 0; i < lanzamientos; i++)
    {
        archivo << left << setw(10) << simulacion[i].dado1 << setw(10) << simulacion[i].dado2 << setw(10) << simulacion[i].sumaTotal << endl;
    }
    archivo.close();
    cout << endl
         << lanzamientos << " lanzamientos guardados correctamente." << endl;
}

void estadisticas()
{
    ifstream archivo("resultados_dados.txt");

    if (!archivo)
    {
        cout << "\n❌ No hay datos registrados.\n"
             << endl;
        return;
    }

    int contador[13] = {0};
    int totalLanzamientos = 0;
    string linea;

    // Saltar comentarios y encabezados
    while (getline(archivo, linea))
    {
        if (linea.empty() || linea[0] == '#')
        {
            continue;
        }
        // Leer los datos
        istringstream iss(linea);
        int d1, d2, suma;
        if (iss >> d1 >> d2 >> suma)
        {
            contador[suma]++;
            totalLanzamientos++;
        }
    }

    archivo.close();

    if (totalLanzamientos == 0)
    {
        cout << "\nNo hay lanzamientos registrados.\n"
             << endl;
        return;
    }

    // Mostrar estadísticas mejoradas
    cout << "\n╔══════════════ ESTADÍSTICAS ACUMULADAS ═══════════════╗" << endl;
    cout << "  Total de lanzamientos: " << totalLanzamientos << endl;
    cout << "╚══════════════════════════════════════════════════════╝\n"
         << endl;

    cout << fixed << setprecision(2);
    cout << left
         << setw(10) << "Suma"
         << setw(15) << "Frecuencia"
         << setw(15) << "Porcentaje"
         << "Gráfico" << endl;
    cout << string(70, '-') << endl;

    for (int i = 2; i <= 12; i++)
    {
        double porcentaje = (contador[i] * 100.0) / totalLanzamientos;
        int barras = (int)(porcentaje / 2);

        cout << left
             << setw(10) << i
             << setw(15) << contador[i]
             << setw(13) << (to_string((int)porcentaje) + "%")
             << string(barras, '|') << endl;
    }
    cout << endl;

    archivo.close();

    if (totalLanzamientos == 0)
    {
        cout << "\nNo hay lanzamientos registrados.\n"
             << endl;
        return;
    }
    mostrarEstadisticas(contador, totalLanzamientos);
}

void mostrarEstadisticas(int contador[], int totalLanzamientos)
{
    cout << "\n══════════════ ESTADÍSTICAS ACUMULADAS ═══════════════" << endl;
    cout << "  Total de lanzamientos: " << totalLanzamientos << endl;
    cout << "══════════════════════════════════════════════════════\n"
         << endl;

    cout << fixed << setprecision(1);
    cout << left
         << setw(8) << "Suma"
         << setw(12) << "Veces"
         << setw(12) << "Porcentaje"
         << "Distribución" << endl;
    cout << string(70, '=') << endl;

    int maxContador = 0;
    for (int i = 2; i <= 12; i++)
    {
        if (contador[i] > maxContador)
            maxContador = contador[i];
    }

    for (int i = 2; i <= 12; i++)
    {
        double porcentaje = (contador[i] * 100.0) / totalLanzamientos;
        int barras = (contador[i] * 30) / maxContador;

        cout << left
             << setw(8) << i
             << setw(12) << contador[i]
             << setw(11) << (to_string((int)porcentaje) + "%")
             << string(barras, '|');

        if (barras > 0)
            cout << " " << porcentaje << "%";

        cout << endl;
    }

    cout << string(70, '-') << endl;
}

void partidaNueva()
{
    ofstream archivo("resultados_dados.txt");

    if (!archivo)
    {
        cout << "Error al reiniciar la partida." << endl;
        return;
    }

    archivo.close();

    cout << "Partida nueva iniciada. Historial borrado." << endl;
}

int contarLanzamientosPrevios()
{
    ifstream archivo("resultados_dados.txt");

    int contador = 0;
    string linea;

    if (!archivo)
        return 0;

    getline(archivo, linea);

    while (getline(archivo, linea))
    {
        contador++;
    }

    archivo.close();
    return contador;
}

void validacion(int &lanzamientos)
{
    while (lanzamientos < 1 || cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa un número a partir del 1 para jugar." << endl;
        cin >> lanzamientos;
    }
}

void validacionMenu(int &opc)
{
    while (opc < 1 || opc > 4 || cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Error. Ingresa una opción válida del menú." << endl;
        cin >> opc;
    }
}

void final()
{
    cout << endl
         << endl
         << "--------------------- Gracias ------------------------" << endl
         << endl;
}