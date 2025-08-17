#include "buscar.h"
#include <iostream>
#include "persona.h"
#include <memory>


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

