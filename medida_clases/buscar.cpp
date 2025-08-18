#include <iomanip>

#include "buscar.h"
#include "persona.h"
#include "generador.h"
#include <algorithm>

// Constantes para mejor mantenibilidad
namespace {
    const int GRUPO_A_LIMITE = 39;
    const int GRUPO_B_LIMITE = 79;
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

const Persona Buscar::encontrarPersonaMasRicaPorValor(const std::vector<Persona> grupo) {
 

    Persona personaMasRica = grupo[0];
    double maxPatrimonio = personaMasRica.getPatrimonio();

    for (const auto& persona : grupo) {
        double patrimonioActual = persona.getPatrimonio();
        if (patrimonioActual > maxPatrimonio) {
            maxPatrimonio = patrimonioActual;
            personaMasRica = persona;
        }
    }
    return personaMasRica;
}


void Buscar::mostrarTop3CiudadesPatrimonio(const std::vector<Persona>& personas) {
    std::vector<std::pair<std::string, double>> promedios;
    
    for (const auto& ciudad : ciudadesColombia) {
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
    for (size_t i = 0; i < 3 && i < promedios.size(); ++i) {  
        std::cout << i+1 << ". " << promedios[i].first      // nombre de la ciudad
                << ": $" << std::fixed << std::setprecision(2)  
                << promedios[i].second << "\n";           // promedio de patrimonio con 2 decimales
    }  
}

void Buscar::mostrarTop3CiudadesPatrimonioPorValor(const std::vector<Persona> personas) {
    std::vector<std::pair<std::string, double>> promedios;
    
    for (const auto& ciudad : ciudadesColombia) {
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
    for (size_t i = 0; i < 3 && i < promedios.size(); ++i) {  
        std::cout << i+1 << ". " << promedios[i].first      // nombre de la ciudad
                << ": $" << std::fixed << std::setprecision(2)  
                << promedios[i].second << "\n";           // promedio de patrimonio con 2 decimales
    }  
}

// Función auxiliar para mostrar la persona más rica por ciudad
void Buscar::mostrarPersonaMasRicaPorCiudad(const std::vector<Persona>& personas) {
    for (const auto& ciudad : ciudadesColombia) {
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

// Función auxiliar para mostrar la persona más rica por ciudad
void Buscar::mostrarPersonaMasRicaPorCiudadPorValor(const std::vector<Persona> personas) {
    for (const auto& ciudad : ciudadesColombia) {
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

void Buscar::contarPersonaPatrimonioMayor1000MillonesPorValor(const std::vector<Persona> personas) {
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

// Función auxiliar para mostrar la persona más rica de un grupo con mensaje personalizado
void Buscar::mostrarPersonaMasRicaGrupoPorValor(const std::vector<Persona> grupo, const std::string nombreGrupo) {
    Persona personaMasRica = encontrarPersonaMasRicaPorValor(grupo);
    std::cout << "\nPersona más rica en el grupo " << nombreGrupo << ": ";
    personaMasRica.mostrar();
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

void Buscar::personaConMayorPatrimonioPorValor(const std::vector<Persona> personas) {
    dianYear(personas);
    
    if (personas.empty()) {
        throw std::runtime_error("Vector de personas vacío");
    }

    // Encontrar persona más rica global
    Persona personaMasRicaGlobal = personas[0];
    double maxPatrimonioGlobal = personaMasRicaGlobal.getPatrimonio();

    for (const auto& persona : personas) {
        double patrimonioActual = persona.getPatrimonio();
        if (patrimonioActual > maxPatrimonioGlobal) {
            maxPatrimonioGlobal = patrimonioActual;
            personaMasRicaGlobal = persona;
        }
    }

    std::cout << "Esta es la persona más rica del País 💰 ";
    personaMasRicaGlobal.mostrar();
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

void Buscar::dianYearPorValor(const std::vector<Persona> personas) {
    grupoA.clear();
    grupoB.clear();
    grupoC.clear();

    for (const auto& persona : personas) {
        std::string id = persona.getId();
        int ultimosDos = std::stoi(id.substr(id.size() - 2)); // Obtengo los ultimos dos digitos de la cedula

        if (ultimosDos <= GRUPO_A_LIMITE) {
            grupoA_val.push_back(persona);
        } else if (ultimosDos <= GRUPO_B_LIMITE) {
            grupoB_val.push_back(persona);
        } else {
            grupoC_val.push_back(persona);
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

void Buscar :: contarPersonasPorCalendarioPorValor (const std:: vector<Persona> personas) {

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

void Buscar::sacarMayor( Persona *personaMayor , Persona *personaComparar)
{
    std::string fechaNacimientoMayor = personaMayor->getFechaNacimiento();
    std::string fechaNacimientoComparar = personaComparar->getFechaNacimiento(); 

    //Comparar años

    int yearPersonaMayor = std::stoi(fechaNacimientoMayor.substr(fechaNacimientoMayor.rfind("/") + 1));
    int yearPersonaComparar = std::stoi(fechaNacimientoComparar.substr(fechaNacimientoComparar.rfind("/") + 1)); 

    if (yearPersonaMayor > yearPersonaComparar)
    {
        *personaMayor = *personaComparar;
        return; 
    }

    //Comparar meses

    int posPrimerSlash = fechaNacimientoMayor.find('/');
    int posSegundoSlash = fechaNacimientoMayor.find('/', posPrimerSlash + 1);
    int mesPersonaMayor = std::stoi(fechaNacimientoMayor.substr(posPrimerSlash + 1, posSegundoSlash - posPrimerSlash - 1));

    int posPrimerSlashComparar = fechaNacimientoComparar.find('/');
    int posSegundoSlashComparar = fechaNacimientoComparar.find('/', posPrimerSlashComparar + 1);
    int mesPersonaComparar = std::stoi(fechaNacimientoComparar.substr(posPrimerSlashComparar + 1, posSegundoSlashComparar - posPrimerSlashComparar - 1));

    if ((yearPersonaComparar == yearPersonaMayor) && (mesPersonaMayor > mesPersonaComparar))
    {
        *personaMayor = *personaComparar;
        return; 
    }
   
    //Comparar días
    
    int diaMayor = std::stoi(fechaNacimientoMayor.substr(0 , fechaNacimientoMayor.find('/')));
    int diaMenor = std::stoi(fechaNacimientoComparar.substr(0 , fechaNacimientoComparar.find('/'))); 

    if((yearPersonaComparar == yearPersonaMayor) && (mesPersonaComparar == mesPersonaMayor) && (diaMayor > diaMenor))
    {
        *personaMayor = *personaComparar;
        return; 
    }

}
void Buscar::sacarMayorPorCuidad(std::vector<Persona>* personas)
{
    size_t tammano = ciudadesColombia.size();

    std::vector<Persona> personasMasRicas;
    personasMasRicas.reserve(tammano); 
    
    size_t tam = personas->size(); 

    Persona *personaMayor = &(*personas)[0]; 

    for (size_t i = 0 ; i < tammano ; i++)
    {
        std::string ciudadMomento = ciudadesColombia[i];


        //Sacar una persona cualquiera de la cuidad que estamos buscando
        for(size_t k = 0 ; k < tam ; k++)
        {
            if((*personas)[k].getCiudadNacimiento() == ciudadMomento)
            {
                personaMayor = &(*personas)[k];
                break;  
            }
        }

        //Comparar edades, debe salir de ultimas el más longevo de todos
        for(size_t j = 0 ; j < tam ; j++)
        {
            if(ciudadMomento == (*personas)[j].getCiudadNacimiento())
            {
                sacarMayor(personaMayor , &(*personas)[j]); 
            }
            
        }

        personasMasRicas.emplace_back(*personaMayor); 

    }

    for (size_t i = 0 ; i < tammano ; i++)
    {
        std::cout << "------------------La persona más longeva de " << personasMasRicas[i].getCiudadNacimiento() << " es: ----------------------------" << std::endl;
        personasMasRicas[i].mostrar();
        std::cout << std::endl; 
    }
} 


Persona Buscar::sacarMayorPorValor (Persona personaMayor , Persona personaComparar)
{
    std::string fechaNacimientoMayor = personaMayor.getFechaNacimiento();
    std::string fechaNacimientoComparar = personaComparar.getFechaNacimiento(); 

    //Comparar años

    int yearPersonaMayor = std::stoi(fechaNacimientoMayor.substr(fechaNacimientoMayor.rfind("/") + 1));
    int yearPersonaComparar = std::stoi(fechaNacimientoComparar.substr(fechaNacimientoComparar.rfind("/") + 1)); 

    if (yearPersonaMayor > yearPersonaComparar)
    {
        personaMayor = personaComparar;
        return personaMayor; 
    }

    //Comparar meses

    int posPrimerSlash = fechaNacimientoMayor.find('/');
    int posSegundoSlash = fechaNacimientoMayor.find('/', posPrimerSlash + 1);
    int mesPersonaMayor = std::stoi(fechaNacimientoMayor.substr(posPrimerSlash + 1, posSegundoSlash - posPrimerSlash - 1));

    int posPrimerSlashComparar = fechaNacimientoComparar.find('/');
    int posSegundoSlashComparar = fechaNacimientoComparar.find('/', posPrimerSlashComparar + 1);
    int mesPersonaComparar = std::stoi(fechaNacimientoComparar.substr(posPrimerSlashComparar + 1, posSegundoSlashComparar - posPrimerSlashComparar - 1));

    if ((yearPersonaComparar == yearPersonaMayor) && (mesPersonaMayor > mesPersonaComparar))
    {
        personaMayor = personaComparar;
        return personaMayor; 
    }
   
    //Comparar días
    
    int diaMayor = std::stoi(fechaNacimientoMayor.substr(0 , fechaNacimientoMayor.find('/')));
    int diaMenor = std::stoi(fechaNacimientoComparar.substr(0 , fechaNacimientoComparar.find('/'))); 

    if((yearPersonaComparar == yearPersonaMayor) && (mesPersonaComparar == mesPersonaMayor) && (diaMayor > diaMenor))
    {
        personaMayor = personaComparar;
        return personaMayor;
    }

    return personaMayor;


}

void Buscar::sacarMayorPorCuidadPorValor(std::vector<Persona> personas)
{
    size_t tammano = ciudadesColombia.size();

    std::vector<Persona> personasMasRicas;
    personasMasRicas.reserve(tammano); 
    
    size_t tam = personas.size(); 

    Persona personaMayor = personas[0]; 

    for (size_t i = 0 ; i < tammano ; i++)
    {
        std::string ciudadMomento = ciudadesColombia[i];


        //Sacar una persona cualquiera de la cuidad que estamos buscando
        for(size_t k = 0 ; k < tam ; k++)
        {
            if(personas[k].getCiudadNacimiento() == ciudadMomento)
            {
                personaMayor = personas[k];
                break;  
            }
        }

        //Comparar edades, debe salir de ultimas el más longevo de todos
        for(size_t j = 0 ; j < tam ; j++)
        {
            if(ciudadMomento == personas[j].getCiudadNacimiento())
            {
                personaMayor = sacarMayorPorValor(personaMayor , personas[j]); 
            }
            
        }

        personasMasRicas.emplace_back(personaMayor); 

    }

    for (size_t i = 0 ; i < tammano ; i++)
    {
        std::cout << "------------------La persona más longeva de " << personasMasRicas[i].getCiudadNacimiento() << " es: ----------------------------" << std::endl;
        personasMasRicas[i].mostrar();
        std::cout << std::endl; 
    }
} 

void Buscar::buscarPersonas18añosDeclarenRenta(std::vector<Persona>* personas)
{

    size_t tam = personas->size(); 
    //Fecha de hoy
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);

    int currentYear = datetime.tm_year + 1900;
    int currentDia = datetime.tm_mday;
    int currentMes = datetime.tm_mon + 1;

    std::vector<Persona> personas18QueDecalren;
    personas18QueDecalren.reserve(10); 
      

    for (size_t i = 0; i < tam ; i++)
    {
        

        std::string fechaNacimientoComparar = (*personas)[i].getFechaNacimiento(); 

        //Comparar años
    
        int yearPersonaComparar = std::stoi(fechaNacimientoComparar.substr(fechaNacimientoComparar.rfind("/") + 1)); 
    
        //Comparar meses
    
        int posPrimerSlashComparar = fechaNacimientoComparar.find('/');
        int posSegundoSlashComparar = fechaNacimientoComparar.find('/', posPrimerSlashComparar + 1);
        int mesPersonaComparar = std::stoi(fechaNacimientoComparar.substr(posPrimerSlashComparar + 1, posSegundoSlashComparar - posPrimerSlashComparar - 1));
    
        //Comparar días
        
        int diaMenor = std::stoi(fechaNacimientoComparar.substr(0 , fechaNacimientoComparar.find('/'))); 
    
        //Si tiene 18
        if(((currentYear - yearPersonaComparar) == 18) && (currentMes >= mesPersonaComparar) && (currentDia >= diaMenor))
        {
            if((*personas)[i].getDeclaranteRenta())
            {
                personas18QueDecalren.emplace_back((*personas)[i]); 
            }
        }
    }

    std::cout << "Las primeras personas que declaran a los 18 son:" << std::endl; 

    if(personas18QueDecalren.size() >= 10)
    {
        for(size_t i = 0 ;  i < 10 ; i++)
        {
            personas18QueDecalren[i].mostrar(); 
        }
    } else
    {
        for(size_t i = 0 ;  i < personas18QueDecalren.size() ; i++)
        {
            personas18QueDecalren[i].mostrar(); 
        }
    }
    
    std::cout << "En total hay " << personas18QueDecalren.size() << " que declaran a los 18" << std::endl; 
   
}

void Buscar::buscarPersonas18añosDeclarenRentaPorValor(std::vector<Persona> personas)
{

    size_t tam = personas.size(); 
    //Fecha de hoy
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);

    int currentYear = datetime.tm_year + 1900;
    int currentDia = datetime.tm_mday;
    int currentMes = datetime.tm_mon + 1;

    std::vector<Persona> personas18QueDecalren;
    personas18QueDecalren.reserve(10); 
      

    for (size_t i = 0; i < tam ; i++)
    {
        

        std::string fechaNacimientoComparar = (personas)[i].getFechaNacimiento(); 

        //Comparar años
    
        int yearPersonaComparar = std::stoi(fechaNacimientoComparar.substr(fechaNacimientoComparar.rfind("/") + 1)); 
    
        //Comparar meses
    
        int posPrimerSlashComparar = fechaNacimientoComparar.find('/');
        int posSegundoSlashComparar = fechaNacimientoComparar.find('/', posPrimerSlashComparar + 1);
        int mesPersonaComparar = std::stoi(fechaNacimientoComparar.substr(posPrimerSlashComparar + 1, posSegundoSlashComparar - posPrimerSlashComparar - 1));
    
        //Comparar días
        
        int diaMenor = std::stoi(fechaNacimientoComparar.substr(0 , fechaNacimientoComparar.find('/'))); 
    
        //Si tiene 18
        if(((currentYear - yearPersonaComparar) == 18) && (currentMes >= mesPersonaComparar) && (currentDia >= diaMenor))
        {
            if((personas)[i].getDeclaranteRenta())
            {
                personas18QueDecalren.emplace_back((personas)[i]); 
            }
        }
    }

    std::cout << "Las primeras personas que declaran a los 18 son:" << std::endl; 

    if(personas18QueDecalren.size() >= 10)
    {
        for(size_t i = 0 ;  i < 10 ; i++)
        {
            personas18QueDecalren[i].mostrar(); 
        }
    } else
    {
        for(size_t i = 0 ;  i < personas18QueDecalren.size() ; i++)
        {
            personas18QueDecalren[i].mostrar(); 
        }
    }
    
    std::cout << "En total hay " << personas18QueDecalren.size() << " que declaran a los 18" << std::endl; 
   
}