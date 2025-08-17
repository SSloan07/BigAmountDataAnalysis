#include "buscar.h"
#include <iostream>
#include "persona.h"
#include <memory>
#include <ctime>


void Buscar::sacarMayor( Persona *personaMayor , Persona *personaComparar)
{
    std::string fechaNacimientoMayor = personaMayor->fechaNacimiento;
    std::string fechaNacimientoComparar = personaComparar->fechaNacimiento; 

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
            if((*personas)[k].ciudadNacimiento == ciudadMomento)
            {
                personaMayor = &(*personas)[k];
                break;  
            }
        }

        //Comparar edades, debe salir de ultimas el más longevo de todos
        for(size_t j = 0 ; j < tam ; j++)
        {
            if(ciudadMomento == (*personas)[j].ciudadNacimiento)
            {
                sacarMayor(personaMayor , &(*personas)[j]); 
            }
            
        }

        personasMasRicas.emplace_back(*personaMayor); 

    }

    for (size_t i = 0 ; i < tammano ; i++)
    {
        std::cout << "------------------La persona más longeva de " << personasMasRicas[i].ciudadNacimiento << " es: ----------------------------" << std::endl;
        personasMasRicas[i].mostrar();
        std::cout << std::endl; 
    }
} 


Persona Buscar::sacarMayorPorValor (Persona personaMayor , Persona personaComparar)
{
    std::string fechaNacimientoMayor = personaMayor.fechaNacimiento;
    std::string fechaNacimientoComparar = personaComparar.fechaNacimiento; 

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
            if(personas[k].ciudadNacimiento == ciudadMomento)
            {
                personaMayor = personas[k];
                break;  
            }
        }

        //Comparar edades, debe salir de ultimas el más longevo de todos
        for(size_t j = 0 ; j < tam ; j++)
        {
            if(ciudadMomento == personas[j].ciudadNacimiento)
            {
                personaMayor = sacarMayorPorValor(personaMayor , personas[j]); 
            }
            
        }

        personasMasRicas.emplace_back(personaMayor); 

    }

    for (size_t i = 0 ; i < tammano ; i++)
    {
        std::cout << "------------------La persona más longeva de " << personasMasRicas[i].ciudadNacimiento << " es: ----------------------------" << std::endl;
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
        

        std::string fechaNacimientoComparar = (*personas)[i].fechaNacimiento; 

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
            if((*personas)[i].declaranteRenta)
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
        

        std::string fechaNacimientoComparar = (personas)[i].fechaNacimiento; 

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
            if((personas)[i].declaranteRenta)
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

