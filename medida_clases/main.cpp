#include <iostream>
#include <vector>
#include <limits>
#include <memory>
#include "persona.h"
#include "generador.h"
#include "monitor.h"
#include "buscar.h"

/**
 * Muestra el menú principal de la aplicación.
 * 
 * POR QUÉ: Guiar al usuario a través de las funcionalidades disponibles.
 * CÓMO: Imprimiendo las opciones en consola.
 * PARA QUÉ: Interacción amigable con el usuario.
 */
void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Mostrar estadísticas de rendimiento";
    std::cout << "\n5. Exportar estadísticas a CSV";
    std::cout << "\n6. Buscar la persona con mayor patrimonio del país"; 
    std::cout << "\n7. Buscar la persona con mayor patrimonio por ciudad ";
    std::cout << "\n8. Buscar las 3 ciudades con mayor patrimonio en promedio ";
    std::cout << "\n9. Buscar la persona con mayor patrimonio por grupo del calendario de la DIAN"; 
    std::cout << "\n10. Contar personas por calendario"; 
    std::cout << "\n11. Contar personas con un patrimonio mayor a 1000 Millones";
    std::cout << "\n12. Salir"; 
    std::cout << "\nSeleccione una opción: ";
}

/**
 * Punto de entrada principal del programa.
 * 
 * POR QUÉ: Iniciar la aplicación y manejar el flujo principal.
 * CÓMO: Mediante un bucle que muestra el menú y procesa la opción seleccionada.
 * PARA QUÉ: Ejecutar las funcionalidades del sistema.
 */
int main() {
    srand(time(nullptr)); // Semilla para generación aleatoria
    
    // Puntero inteligente para gestionar la colección de personas
    // POR QUÉ: Evitar fugas de memoria y garantizar liberación automática.
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    
    Monitor monitor; // Monitor para medir rendimiento
    Buscar buscador;

    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        // Variables locales para uso en los casos
        size_t tam = 0;
        int indice;
        std::string idBusqueda;
        
        // Iniciar medición de tiempo y memoria para la operación actual
        long memoria_inicio = monitor.obtener_memoria();
        
        switch(opcion) {
            case 0: { // Crear nuevo conjunto de datos
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                //Iniciar el contador
                monitor.iniciar_tiempo();

                // Generar el nuevo conjunto de personas
                auto nuevasPersonas = generarColeccion(n);
                tam = nuevasPersonas.size();
                
                // Mover el conjunto al puntero inteligente (propiedad única)
                personas = std::make_unique<std::vector<Persona>>(std::move(nuevasPersonas));
                
                // Medir tiempo y memoria usada
                double tiempo_gen = monitor.detener_tiempo();if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                // Registrar la operación
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: { // Mostrar resumen de todas las personas
                
                //Iniciar tiempo
                monitor.iniciar_tiempo();

                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\n=== RESUMEN DE PERSONAS (" << tam << ") ===\n";
                for(size_t i = 0; i < tam; ++i) {
                    std::cout << i << ". ";
                    (*personas)[i].mostrarResumen();
                    std::cout << "\n";
                }
                
                double tiempo_mostrar = monitor.detener_tiempo();
                long memoria_mostrar = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar resumen", tiempo_mostrar, memoria_mostrar);
                
                break;
            }
                
            case 2: { // Mostrar detalle por índice


                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                
                if(std::cin >> indice) {

                    //Iniciar tiempo
                    monitor.iniciar_tiempo();

                    if(indice >= 0 && static_cast<size_t>(indice) < tam) {
                        (*personas)[indice].mostrar();
                    } else {
                        std::cout << "Índice fuera de rango!\n";
                    }
                } else {
                    std::cout << "Entrada inválida!\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                
                
                double tiempo_detalle = monitor.detener_tiempo();
                long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Mostrar detalle", tiempo_detalle, memoria_detalle);
                break;
            }
                
            case 3: { // Buscar por ID
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;

                //Iniciar tiempo
                monitor.iniciar_tiempo();
                
                if(const Persona* encontrada = buscarPorID(*personas, idBusqueda)) {
                    encontrada->mostrar();
                } else {
                    std::cout << "No se encontró persona con ID " << idBusqueda << "\n";
                }
                
                double tiempo_busqueda = monitor.detener_tiempo();
                long memoria_busqueda = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Buscar por ID", tiempo_busqueda, memoria_busqueda);
                break;
            }
                
            case 4: // Mostrar estadísticas de rendimiento

            
                monitor.mostrar_resumen();
                break;
                
            case 5: // Exportar estadísticas a CSV
                monitor.exportar_csv();
                break;
            case 6: { // Mostrar persona con mayor patrimonio
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                // Iniciar tiempo
                monitor.iniciar_tiempo();
                
                buscador.personaConMayorPatrimonio(*personas);
                
                double tiempo_rico = monitor.detener_tiempo();
                long memoria_rico = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Persona más rica", tiempo_rico, memoria_rico);
                break;
            }
            case 7 : { // Mostrar persona más rica por ciudad
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                // Iniciar tiempo
                monitor.iniciar_tiempo();
                
                buscador.mostrarPersonaMasRicaPorCiudad(*personas);
                
                double tiempo_ricoCiudad = monitor.detener_tiempo();
                long memoria_ricoCiudad = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Persona más rica por ciudad", tiempo_ricoCiudad, memoria_ricoCiudad);
                break;
            }
            case 8 : { // Mostrar persona más rica por ciudad
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                // Iniciar tiempo
                monitor.iniciar_tiempo();
                
                buscador.mostrarTop3CiudadesPatrimonio(*personas);
                
                double tiempo_promedioPatrimonioCiudad = monitor.detener_tiempo();
                long memoria_promedioPatrimonioCiudad = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Promedio del patrimonio por ciudad", tiempo_promedioPatrimonioCiudad, memoria_promedioPatrimonioCiudad);
                break;
            }
            case 9 : { // Mostrar persona más rica por calendario tributario de la DIAN 
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }

                // Primero necesitamos clasificar las personas en grupos
                buscador.dianYear(*personas); // Esto llena grupoA, grupoB, grupoC

                // Iniciar tiempo
                monitor.iniciar_tiempo();
                
                // Mostrar para cada grupo
                std::cout << "\n=== Personas más ricas por grupo ===";
                buscador.mostrarPersonaMasRicaGrupo(buscador.grupoA, "A");
                buscador.mostrarPersonaMasRicaGrupo(buscador.grupoB, "B");
                buscador.mostrarPersonaMasRicaGrupo(buscador.grupoC, "C");
                
                double tiempo_ricoGrupo = monitor.detener_tiempo();
                long memoria_ricoGrupo = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Persona más rica por ciudad", tiempo_ricoGrupo, memoria_ricoGrupo);
                break;
            }

            case 10 :{ // Contar y validad personas por el calendario tributario de la DIAN
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                monitor.iniciar_tiempo();
                buscador.contarPersonasPorCalendario(*personas); 
                double tiempo_gruposDian = monitor.detener_tiempo();
                long memoria_gruposDian = monitor.obtener_memoria() - memoria_inicio;
                monitor.registrar("Contar personas por el calendario tributario de la DIAN", tiempo_gruposDian, memoria_gruposDian);
                break; 
            }
            case 11 :{
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                monitor.iniciar_tiempo(); 
                buscador.contarPersonaPatrimonioMayor1000Millones(*personas); 
                double tiempo_personasPatrimonioMayor1000Millones = monitor.detener_tiempo(); 
                long memoria_personasPatrimonioMayor1000Millones = monitor.obtener_memoria() -memoria_inicio; 
                monitor.registrar("Contar personas con un patrimonio mayor a 1000 Millones", tiempo_personasPatrimonioMayor1000Millones, memoria_personasPatrimonioMayor1000Millones);
                break; 
            }
                

            case 12: { //salir
                std::cout << "Saliendo...\n";
                break;
            } // Salir
                
            default:
                std::cout << "Opción inválida!\n";
        }
        
        // Mostrar estadísticas de la operación (excepto para opciones 4,5,6)
        if ((opcion >= 0 && opcion <= 3) || (opcion >= 6 && opcion <= 11)) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
        
    } while(opcion != 12);
    
    return 0;
}