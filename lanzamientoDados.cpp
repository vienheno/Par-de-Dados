#include <iostream>
#include <string>
#include <iomanip>
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

// ============================================
// FUNCIÓN PRINCIPAL
// ============================================
int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");
    
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
    }
    
    return cantidad;
}

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
