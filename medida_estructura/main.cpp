#include <iostream>
#include <vector>
#include <limits> // Para manejo de límites de entrada
#include <memory> // Para std::unique_ptr y std::make_unique
#include "persona.h"
#include "generador.h"
#include "monitor.h" // Nuevo header para monitoreo
#include "buscar.h"

void mostrarMenu() {
    std::cout << "\n\n=== MENÚ PRINCIPAL ===";
    std::cout << "\n0. Crear nuevo conjunto de datos";
    std::cout << "\n1. Mostrar resumen de todas las personas";
    std::cout << "\n2. Mostrar detalle completo por índice";
    std::cout << "\n3. Buscar persona por ID";
    std::cout << "\n4. Mostrar estadísticas de rendimiento";
    std::cout << "\n5. Exportar estadísticas a CSV";
    std::cout << "\n6. Salir";
    std::cout << "\n7. Más longevo del país";
    std::cout << "\n8. Más longevo por cuidad"; 
    std::cout << "\n9. Buscar personas de 18 años que decalren renta"; 
    std::cout << "\nSeleccione una opción: ";
}

int main() {
    srand(time(nullptr));
    
    // Usar unique_ptr para manejar la colección de personas
    std::unique_ptr<std::vector<Persona>> personas = nullptr;
    Monitor monitor;
    Buscar buscar; 
    
    int opcion;
    do {
        mostrarMenu();
        std::cin >> opcion;
        
        size_t tam = 0;
        int indice;
        std::string idBusqueda;
        
        // Iniciar medición de tiempo y memoria para esta operación
        monitor.iniciar_tiempo();
        long memoria_inicio = monitor.obtener_memoria();
        
        switch(opcion) {
            case 0: {
                int n;
                std::cout << "\nIngrese el número de personas a generar: ";
                std::cin >> n;
                
                if (n <= 0) {
                    std::cout << "Error: Debe generar al menos 1 persona\n";
                    break;
                }
                
                // Generar el nuevo conjunto de datos
                personas = std::make_unique<std::vector<Persona>>(generarColeccion(n));
                tam = personas->size();
                
                double tiempo_gen = monitor.detener_tiempo();
                long memoria_gen = monitor.obtener_memoria() - memoria_inicio;
                
                std::cout << "Generadas " << tam << " personas en " 
                          << tiempo_gen << " ms, Memoria: " << memoria_gen << " KB\n";
                
                monitor.registrar("Crear datos", tiempo_gen, memoria_gen);
                break;
            }
                
            case 1: {
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
                
            case 2: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                tam = personas->size();
                std::cout << "\nIngrese el índice (0-" << tam-1 << "): ";
                if(std::cin >> indice) {
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
                
            case 3: {
                if (!personas || personas->empty()) {
                    std::cout << "\nNo hay datos disponibles. Use opción 0 primero.\n";
                    break;
                }
                
                std::cout << "\nIngrese el ID a buscar: ";
                std::cin >> idBusqueda;
                
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
                
            case 4:
                monitor.mostrar_resumen();
                break;
                
            case 5:
                monitor.exportar_csv();
                break;
                
            case 6:
                std::cout << "Saliendo...\n";
                break;


            {

                case 7:
    
                    //REFERENCIA
                    std::cout << "La persona más longeva es (Por referencia):" << std::endl;
    
                    //Iniciar el contador
                    monitor.iniciar_tiempo();
                    
                    Persona *personaMayor = &(*personas)[0]; 
    
                    tam = personas->size(); 
                                    
                    for(size_t i = 1 ; i < tam ; i++)
                    {
                        buscar.sacarMayor(personaMayor, &(*personas)[i]);
                    }
    
                    personaMayor->mostrar(); 
    
                    double tiempo_detalle = monitor.detener_tiempo();
                    long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                    monitor.registrar("Buscar persona longeva por referencia", tiempo_detalle, memoria_detalle);
    
                    //VALOR
                    std::cout << "La persona más longeva es (Por valor):" << std::endl;
    
                    //Iniciar el contador
                    monitor.iniciar_tiempo();
                    
                    Persona personaMayorValor = (*personas)[0]; 
    
                    tam = personas->size(); 
                                    
                    for(size_t i = 1 ; i < tam ; i++)
                    {
                    personaMayorValor = buscar.sacarMayorPorValor(personaMayorValor , (*personas)[i]);
                    }
    
                    personaMayorValor.mostrar(); 
    
                    tiempo_detalle = monitor.detener_tiempo();
                    memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                    monitor.registrar("Buscar persona longeva por valor", tiempo_detalle, memoria_detalle);
    
    
                    break;
                }
    
                {
                    case 8:
                    std::cout << "Las personas más longevas de cada país son (Por referencia):" << std::endl;
    
                    
                    //Iniciar el contador
                    monitor.iniciar_tiempo();
    
                    //Buscar personas mayores por cuidad
                    buscar.sacarMayorPorCuidad(personas.get());
    
                    double tiempo_detalle = monitor.detener_tiempo();
                    long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                    monitor.registrar("Buscar persona longeva por cuidades por referencia", tiempo_detalle, memoria_detalle);
    
                    std::cout << "Las personas más longevas de cada país son (Por valor):" << std::endl;
    
                    
                    //Iniciar el contador
                    monitor.iniciar_tiempo();
    
                    //Buscar personas mayores por cuidad
                    buscar.sacarMayorPorCuidadPorValor(*personas);
    
                    tiempo_detalle = monitor.detener_tiempo();
                    memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                    monitor.registrar("Buscar persona longeva por cuidades por valor", tiempo_detalle, memoria_detalle);
    
                    break;
                }
    
                {
                    case 9:
                    std::cout << "Las primeras 10 personas de 18 año que declaren renta son (Por referencia):" << std::endl;
    
                    
                    //Iniciar el contador
                    monitor.iniciar_tiempo();
    
                    //Buscar personas mayores por cuidad
                    buscar.buscarPersonas18añosDeclarenRenta(personas.get()); 
    
                    double tiempo_detalle = monitor.detener_tiempo();
                    long memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                    monitor.registrar("Personas declarantes con 18 por referencia", tiempo_detalle, memoria_detalle);
    
                    std::cout << "---------------------------------------------------------------------------------------------" << std::endl; 
                    std::cout << "Las primeras 10 personas de 18 año que declaren renta son (Por valor):" << std::endl;
                    
                    //Iniciar el contador
                    monitor.iniciar_tiempo();
    
                    //Buscar personas mayores por cuidad
                    buscar.buscarPersonas18añosDeclarenRentaPorValor(*personas); 
    
                    tiempo_detalle = monitor.detener_tiempo();
                    memoria_detalle = monitor.obtener_memoria() - memoria_inicio;
                    monitor.registrar("Personas declarantes con 18 por valor", tiempo_detalle, memoria_detalle);
    
                    break;
                }
                
            default:
                std::cout << "Opción inválida!\n";
        }
        
        // Mostrar estadísticas para las operaciones principales
        if (opcion >= 0 && opcion <= 3) {
            double tiempo = monitor.detener_tiempo();
            long memoria = monitor.obtener_memoria() - memoria_inicio;
            monitor.mostrar_estadistica("Opción " + std::to_string(opcion), tiempo, memoria);
        }
        
    } while(opcion != 6);
    
    return 0;
}