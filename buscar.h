#ifndef BUSCAR_H
#define BUSCAR_H

#include <vector>
#include <string>
#include "persona.h"

class Buscar {
    public:
        // Métodos públicos
        void personaMasLongeva(const std::vector<Persona>& personas);
        void personaConMayorPatrimonio(const std::vector<Persona>& personas);
        void dianYear(const std::vector<Persona>& personas);
        void contarPersonasPorCalendario(const std::vector<Persona>& personas); 
        // Métodos auxiliares publicos
        const Persona* encontrarPersonaMasRica(const std::vector<Persona*>& grupo);
        void mostrarPersonaMasRicaPorCiudad(const std::vector<Persona>& personas);
        void mostrarPersonaMasRicaGrupo(const std::vector<Persona*>& grupo, const std::string& nombreGrupo);
        void mostrarTop3CiudadesPatrimonio(const std::vector<Persona>& personas); 
        void contarPersonaPatrimonioMayor1000Millones(const std :: vector <Persona>& personas); 
        // Variables miembro publicas
        std::vector<Persona*> grupoA;
        std::vector<Persona*> grupoB;
        std::vector<Persona*> grupoC;

};

#endif // BUSCAR_H