#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
<<<<<<< HEAD

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
=======
#include <vector>
#include <random>
#include <algorithm>

using namespace std;

// ============================================
// CONSTANTES GLOBALES
// ============================================
const int DADO_MIN = 1;
const int DADO_MAX = 6;
const int SUMA_MIN = 2;
const int SUMA_MAX = 12;
const int ANCHO_BARRA = 50;

// ============================================
// ESTRUCTURA DE DATOS
// ============================================
struct lanzamientoDados {
    int dado1;
    int dado2;
    int suma;
    
    // Constructor para inicialización directa
    lanzamientoDados(int d1, int d2) : dado1(d1), dado2(d2), suma(d1 + d2) {}
};

// ============================================
// PROTOTIPOS DE FUNCIONES
// ============================================
void mostrarTitulo();
void mostrarDespedida();
void lanzarDados(int cantidad);
bool preguntarNuevoLanzamiento();
int solicitarCantidadLanzamientos();
void mostrarEstadistica(int suma, int frecuencia, int total);
void mostrarBarraProgreso(double porcentaje);
void mostrarEncabezadoTabla();
void limpiarPantalla();
>>>>>>> origin/rama-juan

// ============================================
// FUNCIÓN PRINCIPAL
// ============================================
int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
<<<<<<< HEAD

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
=======
    
    mostrarTitulo();
    
    do {
        int cantidad = solicitarCantidadLanzamientos();
        lanzarDados(cantidad);
    } while (preguntarNuevoLanzamiento());
    
    mostrarDespedida();
    return 0;
}
// ============================================
// IMPLEMENTACIÓN: INTERFAZ DE USUARIO
// ============================================
/**
 * Limpia la pantalla de forma multiplataforma
 * CAMBIO: Más robusto que system("cls")
 */
void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * Muestra el título del programa un poquito mejorado
 */
void mostrarTitulo() {
    limpiarPantalla();
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║         🎲  SIMULADOR DE LANZAMIENTO DE DADOS  🎲         ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
}

/**
 * Muestra mensaje de despedida
 */
void mostrarDespedida() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║              ¡Gracias por usar el simulador!              ║\n";
    cout << "╚═══════════════════════════════════════════════════════════╝\n\n";
}

/**
 * Muestra el encabezado de la tabla de estadísticas
 */
void mostrarEncabezadoTabla() {
    cout << "\n╔═══════════════════════════════════════════════════════════╗\n";
    cout << "║              📊 ESTADÍSTICAS DE LANZAMIENTOS              ║\n";
    cout << "╠═══════╦══════════╦═══════════╦═══════════════════════════╣\n";
    cout << "║ Suma  ║   Veces  ║    (%)    ║      Distribución         ║\n";
    cout << "╠═══════╬══════════╬═══════════╬═══════════════════════════╣\n";
}

/**
 * Genera una barra de progreso visual representacion gráfica ;)
 * @param porcentaje: Valor entre 0 y 100
 */
void mostrarBarraProgreso(double porcentaje) {
    int barras = static_cast<int>((porcentaje / 100.0) * ANCHO_BARRA);
    cout << "║ ";
    
    for (int i = 0; i < ANCHO_BARRA; i++) {
        if (i < barras) {
            cout << "█";
        } else {
            cout << "░";
        }
    }
    cout << " ║";
}

/**
 * Muestra una línea de estadística formateada, Función modular para evitar repetición
 * @param suma: Número de la suma (2-12)
 * @param frecuencia: Cantidad de veces que apareció
 * @param total: Total de lanzamientos
 */
void mostrarEstadistica(int suma, int frecuencia, int total) {
    double porcentaje = (frecuencia * 100.0) / total;
    
    cout << "║  " << setw(2) << suma << "   ║  " 
         << setw(6) << frecuencia << "  ║  "
         << setw(6) << fixed << setprecision(2) << porcentaje << "%  ║ ";
    
    // Barra de progreso proporcional
    int barras = static_cast<int>((porcentaje / 100.0) * 25);
    for (int i = 0; i < 25; i++) {
        cout << (i < barras ? "█" : "░");
    }
    cout << " ║\n";
}

// ============================================
// IMPLEMENTACIÓN: LÓGICA DE VALIDACIÓN
// ============================================

/**
 * Solicita y valida la cantidad de lanzamientos
 * Función separada para mejor organización
 */
int solicitarCantidadLanzamientos() {
    int cantidad;
    bool entradaValida = false;
    
    while (!entradaValida) {
        cout << " Ingrese la cantidad de lanzamientos: ";
        cin >> cantidad;
        
        if (cin.fail()) {
            // Error de tipo (se ingresó texto en lugar de número)
            cin.clear();
            cin.ignore(10000, '\n');
            cout << " Error: Debe ingresar un número entero.\n\n";
        } else if (cantidad < 1) {
            // Número válido pero fuera de rango
            cout << " Error: La cantidad debe ser mayor o igual a 1.\n\n";
        } else {
            // Entrada válida
            entradaValida = true;
        }
>>>>>>> origin/rama-juan
    }
    
    return cantidad;
}

<<<<<<< HEAD
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
=======
/**
 * Pregunta si se desea realizar otro lanzamiento
 * Manejo de errores y mensajes
 */
bool preguntarNuevoLanzamiento() {
    int opcion;
    bool entradaValida = false;
    
    cout << "\n┌───────────────────────────────────────┐\n";
    cout << "│  ¿Desea realizar otro lanzamiento?   │\n";
    cout << "├───────────────────────────────────────┤\n";
    cout << "│  1 ➜ Sí, continuar                    │\n";
    cout << "│  0 ➜ No, salir                        │\n";
    cout << "└───────────────────────────────────────┘\n";
    cout << "Opción: ";
    
    while (!entradaValida) {
        cin >> opcion;
        
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "❌ Error: Ingrese 1 o 0.\nOpción: ";
        } else if (opcion != 0 && opcion != 1) {
            cout << "❌ Error: Opción inválida. Ingrese 1 o 0.\nOpción: ";
        } else {
            entradaValida = true;
        }
    }
    
    if (opcion == 1) {
        limpiarPantalla();
        mostrarTitulo();
    }
    
    return opcion == 1;
}

// ============================================
// IMPLEMENTACIÓN: LÓGICA PRINCIPAL
// ============================================

void lanzarDados(int cantidad) {
    // ────────────────────────────────────────
    // 1. INICIALIZACIÓN DE ESTRUCTURAS
    // ────────────────────────────────────────
    
    // CAMBIO: Vector en lugar de VLA (C++ estándar)
    vector<lanzamientoDados> lanzamientos;
    lanzamientos.reserve(cantidad); // Optimización: reserva memoria
    
    // CAMBIO: Arreglo único en lugar de 11 variables separadas
    // Índice 0 = suma 2, índice 1 = suma 3, ..., índice 10 = suma 12
    vector<int> frecuencias(11, 0);
    
    // ────────────────────────────────────────
    // 2. GENERADOR DE NÚMEROS ALEATORIOS MODERNO
    // ────────────────────────────────────────
    
    // CAMBIO CRÍTICO: mt19937 en lugar de rand()
    // Ventajas:
    // - Mayor calidad estadística
    // - Período mucho más largo (2^19937 - 1)
    // - Distribución uniforme garantizada
    random_device rd;  // Fuente de entropía del sistema
    mt19937 gen(rd()); // Generador Mersenne Twister
    uniform_int_distribution<> dis(DADO_MIN, DADO_MAX); // Distribución uniforme [1,6]
    
    // ────────────────────────────────────────
    // 3. SIMULACIÓN DE LANZAMIENTOS
    // ────────────────────────────────────────
    
    cout << "\n Lanzando dados";
    for (int i = 0; i < cantidad; i++) {
        // Generar valores de dados
        int dado1 = dis(gen);
        int dado2 = dis(gen);
        
        // Crear lanzamiento con constructor
        lanzamientos.emplace_back(dado1, dado2);
        
        // CAMBIO: Indexación directa en lugar de switch
        // suma - 2 convierte suma [2,12] a índice [0,10]
        frecuencias[lanzamientos[i].suma - 2]++;
        
        // Indicador de progreso visual
        if ((i + 1) % (cantidad / 10 + 1) == 0) {
            cout << ".";
            cout.flush();//función que fuerza el vaciado inmediato del búfer.
        }
    }
    cout << " ✓ Completado\n";
    
    // ────────────────────────────────────────
    // 4. PRESENTACIÓN DE RESULTADOS
    // ────────────────────────────────────────
    
    mostrarEncabezadoTabla();
    
    // CAMBIO: Bucle único en lugar de 22 líneas repetitivas
    for (int suma = SUMA_MIN; suma <= SUMA_MAX; suma++) {
        mostrarEstadistica(suma, frecuencias[suma - 2], cantidad);
    }
    
    cout << "╚═══════╩══════════╩═══════════╩═══════════════════════════╝\n";
    
    // ────────────────────────────────────────
    // 5. ESTADÍSTICAS ADICIONALES
    // ────────────────────────────────────────
    
    // Encontrar el valor más frecuente
    auto maxIt = max_element(frecuencias.begin(), frecuencias.end());
    int sumaMasFrecuente = SUMA_MIN + distance(frecuencias.begin(), maxIt);
    
    cout << "\n📈 Análisis Estadístico:\n";
    cout << "   • Total de lanzamientos: " << cantidad << "\n";
    cout << "   • Suma más frecuente: " << sumaMasFrecuente 
         << " (" << *maxIt << " veces, " 
         << fixed << setprecision(2) << (*maxIt * 100.0 / cantidad) << "%)\n";
    
    // Probabilidad teórica vs observada para el 7
    double probTeorica7 = 16.67; // 6/36
    double probObservada7 = (frecuencias[5] * 100.0) / cantidad;
    cout << "   • Suma 7 (teórica: 16.67%, observada: " 
         << probObservada7 << "%)\n";
}
>>>>>>> origin/rama-juan
