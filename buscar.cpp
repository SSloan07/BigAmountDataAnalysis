#include <iomanip>

#include "buscar.h"
#include "persona.h"
#include "generador.h"
#include <algorithm>

// Constantes para mejor mantenibilidad
namespace {
    const std::vector<std::string> CIUDADES_COLOMBIA = {
        "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga",
        "Pereira", "Santa Marta", "Cúcuta", "Ibagué", "Manizales", "Pasto", "Neiva",
        "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"
    };
    
    const int GRUPO_A_LIMITE = 39;
    const int GRUPO_B_LIMITE = 79;
}

void Buscar::personaMasLongeva(const std::vector<Persona> & personas) {
    /*if (personas.empty()) {
        throw std::runtime_error("Vector de personas vacío");
    }

    //Persona más longeva de todas
    Persona* personaLongeva = const_cast<Persona*>(&personas[0]);    
    
    for(int i = 0 ; i < personas.size() ; i++)
    {

    }*/
}

// Función auxiliar para encontrar la persona con mayor patrimonio en un grupo
const Persona* Buscar::encontrarPersonaMasRica(const std::vector<Persona*>& grupo) {
    if (grupo.empty()) return nullptr;

    const Persona* personaMasRica = grupo[0];
    double maxPatrimonio = personaMasRica->getPatrimonio();

    for (const auto& persona : grupo) {
        double patrimonioActual = persona->getPatrimonio();
        if (patrimonioActual > maxPatrimonio) {
            maxPatrimonio = patrimonioActual;
            personaMasRica = persona;
        }
    }
    return personaMasRica;
}
void Buscar::mostrarTop3CiudadesPatrimonio(const std::vector<Persona>& personas) {
    std::vector<std::pair<std::string, double>> promedios;
    
    for (const auto& ciudad : CIUDADES_COLOMBIA) {
        double total = 0;
        int contador = 0;
        
        for (const auto& persona : personas) {
            if (persona.getCiudadNacimiento() == ciudad) {
                total += persona.getPatrimonio();
                contador++;
            }
        }
        
        if (contador > 0) {
            promedios.emplace_back(ciudad, total/contador);
            // Guardamos el par (ciudad, promedio) en el vector
        }
    }
    
    // Ordena parcialmente el vector para encontrar el TOP 3
    // Solo organiza los 3 primeros elementos como si estuvieran ordenados
    // (es más eficiente que ordenar toda la lista cuando solo necesitamos el top)
    std::partial_sort(
        promedios.begin(),                                   // inicio del rango
        promedios.begin() + std::min(3, (int)promedios.size()), // hasta el tercer elemento (o menos si no hay tantas ciudades)
        promedios.end(),                                    // fin del rango
        [](const auto& a, const auto& b) {                  // criterio de orden: mayor promedio primero
            return a.second > b.second;  
        }
    );  

    // Mostrar los 3 resultados (o menos si no hay suficientes ciudades)
    std::cout << "\n====== TOP 3 CIUDADES ======\n";  
    for (int i = 0; i < 3 && i < promedios.size(); ++i) {  
        std::cout << i+1 << ". " << promedios[i].first      // nombre de la ciudad
                << ": $" << std::fixed << std::setprecision(2)  
                << promedios[i].second << "\n";           // promedio de patrimonio con 2 decimales
    }  
}

// Función auxiliar para mostrar la persona más rica por ciudad
void Buscar::mostrarPersonaMasRicaPorCiudad(const std::vector<Persona>& personas) {
    for (const auto& ciudad : CIUDADES_COLOMBIA) {
        const Persona* personaMasRicaCiudad = nullptr;
        double maxPatrimonioCiudad = -1.0;

        for (const auto& persona : personas) {
            if (persona.getCiudadNacimiento() == ciudad) {
                double patrimonioActual = persona.getPatrimonio();
                if (patrimonioActual > maxPatrimonioCiudad) {
                    maxPatrimonioCiudad = patrimonioActual;
                    personaMasRicaCiudad = &persona;
                }
            }
        }

        if (personaMasRicaCiudad) {
            std::cout << "\nPersona más rica en " << ciudad << ": ";
            personaMasRicaCiudad->mostrar();
        }
    }
}
// Función auxiliar para contar y validar el numero de personas con un patrimonio mayor a 1000 Millones 
void Buscar::contarPersonaPatrimonioMayor1000Millones(const std::vector<Persona>& personas) {
    std::vector<const Persona*> filtrados;

    for (const auto& persona : personas) {
        if (persona.getPatrimonio() >= 1000000000) {  // 1000 millones
            filtrados.push_back(&persona); //Lleno el vector filtrados SOLO con la gente con un patrimonio mayor a 1000 millones
        }
    }

    std::cout << "El número de personas con un patrimonio >= 1000 Millones es: "
              << filtrados.size() << "\n";

    if (filtrados.empty()) {
        return; // nada que mostrar
    }

    // Ordenar de menor a mayor patrimonio
    auto compararPatrimonio = [](const Persona* a, const Persona* b) {
        return a->getPatrimonio() < b->getPatrimonio();  // Esto de acá es una función lambda que recibe el inicio y fin del vector filtrados. Y en esta lina de codigo compara si el patrimonio de la persona anterior es menor a la posterior, en tal caso devuelve true, sino devuelve false. 
    };

    std::sort(filtrados.begin(), filtrados.end(), compararPatrimonio); //Ordena a filtrados deacuerdo a las condiciones devueltas por la función lambda. 

    std::cout << "\n--- 5 personas con menor patrimonio dentro del grupo ---\n";
    for (size_t i = 0; i < 5 && i < filtrados.size(); ++i) {
        filtrados[i]->mostrar();
    }

    std::cout << "\n--- 5 personas con mayor patrimonio dentro del grupo ---\n";
    for (size_t i = (filtrados.size() >= 5 ? filtrados.size() - 5 : 0);
         i < filtrados.size(); ++i) {
        filtrados[i]->mostrar();
    }
}



// Función auxiliar para mostrar la persona más rica de un grupo con mensaje personalizado
void Buscar::mostrarPersonaMasRicaGrupo(const std::vector<Persona*>& grupo, const std::string& nombreGrupo) {
    const Persona* personaMasRica = encontrarPersonaMasRica(grupo);
    if (personaMasRica) {
        std::cout << "\nPersona más rica en el grupo " << nombreGrupo << ": ";
        personaMasRica->mostrar();
    } else {
        std::cout << "\nGrupo " << nombreGrupo << " vacío\n";
    }
}

void Buscar::personaConMayorPatrimonio(const std::vector<Persona>& personas) {
    dianYear(personas);
    
    if (personas.empty()) {
        throw std::runtime_error("Vector de personas vacío");
    }

    // Encontrar persona más rica global
    const Persona* personaMasRicaGlobal = &personas[0];
    double maxPatrimonioGlobal = personaMasRicaGlobal->getPatrimonio();

    for (const auto& persona : personas) {
        double patrimonioActual = persona.getPatrimonio();
        if (patrimonioActual > maxPatrimonioGlobal) {
            maxPatrimonioGlobal = patrimonioActual;
            personaMasRicaGlobal = &persona;
        }
    }

    std::cout << "Esta es la persona más rica del País 💰 ";
    personaMasRicaGlobal->mostrar();
}

void Buscar::dianYear(const std::vector<Persona>& personas) {
    grupoA.clear();
    grupoB.clear();
    grupoC.clear();

    for (const auto& persona : personas) {
        std::string id = persona.getId();
        int ultimosDos = std::stoi(id.substr(id.size() - 2)); // Obtengo los ultimos dos digitos de la cedula

        if (ultimosDos <= GRUPO_A_LIMITE) {
            grupoA.push_back(const_cast<Persona*>(&persona));
        } else if (ultimosDos <= GRUPO_B_LIMITE) {
            grupoB.push_back(const_cast<Persona*>(&persona));
        } else {
            grupoC.push_back(const_cast<Persona*>(&persona));
        }
    }
}
void Buscar :: contarPersonasPorCalendario (const std:: vector<Persona>& personas) {

    dianYear(personas); 

    // Grupo A
    std::cout<< "===================GRUPO A===========================\n";
    std::cout << "En el grupo A hay " << grupoA.size() << " Personas\n";
    size_t startA = (grupoA.size() > 10) ? grupoA.size() - 10 : 0; // Por medio del operador ternario defino el punto limite hasta el que iterara por el grupo, donde si la longitud del grupo es menor o igual a 10 iterará todo el arreglo. Esto nos ayudará a ahorrar varios cientos de ms en la ejecución del codigo. 
    for (size_t i = grupoA.size(); i-- > startA; ) {
        const Persona* persona = grupoA[i];
        persona->mostrar();
    }

    // Grupo B
    std::cout<< "===================GRUPO B===========================\n";
    std::cout << "En el grupo B hay " << grupoB.size() << " Personas\n"; 
    size_t startB = (grupoB.size() > 10) ? grupoB.size() - 10 : 0; // Igual que en A solo que con B
    for (size_t i = grupoB.size(); i-- > startB; ) {
        const Persona* persona = grupoB[i];
        persona->mostrar();
    }

    // Grupo C
    std::cout<< "===================GRUPO C===========================\n";
    std::cout << "En el grupo C hay " << grupoC.size() << " Personas\n"; 
    size_t startC = (grupoC.size() > 10) ? grupoC.size() - 10 : 0; // Igual que en A solo que con C
    for (size_t i = grupoC.size(); i-- > startC; ) {
        const Persona* persona = grupoC[i];
        persona->mostrar();
    }



}