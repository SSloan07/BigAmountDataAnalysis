#ifndef BUSCAR_H
#define BUSCAR_H

#include <iostream>
#include <vector>
#include "persona.h"

class Buscar {

    private:

        const std::vector<std::string> ciudadesColombia = {
            "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
            "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"
        };

    public:

        void sacarMayor(Persona *personaMayor , Persona *personaComparar); 
        void sacarMayorPorCuidad(std::vector<Persona>* personas); 


}; 

#endif