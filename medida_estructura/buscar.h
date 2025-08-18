#ifndef BUSCAR_H
#define BUSCAR_H

#include <vector>
#include <string>
#include "persona.h"

class Buscar {

    private:

        const std::vector<std::string> ciudadesColombia = {
            "Bogotá", "Medellín", "Cali", "Barranquilla", "Cartagena", "Bucaramanga", "Pereira", "Santa Marta", "Cúcuta", "Ibagué",
            "Manizales", "Pasto", "Neiva", "Villavicencio", "Armenia", "Sincelejo", "Valledupar", "Montería", "Popayán", "Tunja"
        };


    public:
        // Métodos públicos
        // Métodos auxiliares publicos

        //Metodos por referencia
        void sacarMayor(Persona *personaMayor , Persona *personaComparar); 
        void sacarMayorPorCuidad(std::vector<Persona>* personas); 
        void buscarPersonas18añosDeclarenRenta(std::vector<Persona>* personas); 
        void personaConMayorPatrimonio(const std::vector<Persona>& personas);
        void mostrarPersonaMasRicaPorCiudad(const std::vector<Persona>& personas);
        void mostrarTop3CiudadesPatrimonio(const std::vector<Persona>& personas); 
        void dianYear(const std::vector<Persona>& personas);
        void mostrarPersonaMasRicaGrupo(const std::vector<Persona*>& grupo, const std::string& nombreGrupo);
        const Persona* encontrarPersonaMasRica(const std::vector<Persona*>& grupo);
        void contarPersonasPorCalendario(const std::vector<Persona>& personas); 
        void contarPersonaPatrimonioMayor1000Millones(const std :: vector <Persona>& personas); 


        //Metodos por valor
        Persona sacarMayorPorValor (Persona personaMayor , Persona personaComparar);
        void sacarMayorPorCuidadPorValor(std::vector<Persona> personas);
        void buscarPersonas18añosDeclarenRentaPorValor(std::vector<Persona> personas); 
        void personaConMayorPatrimonioPorValor(const std::vector<Persona> personas);
        void mostrarPersonaMasRicaPorCiudadPorValor(const std::vector<Persona> personas);
        void mostrarTop3CiudadesPatrimonioPorValor(const std::vector<Persona> personas); 
        void dianYearPorValor(const std::vector<Persona> personas);
        void mostrarPersonaMasRicaGrupoPorValor(const std::vector<Persona> grupo, const std::string nombreGrupo);
        const Persona encontrarPersonaMasRicaPorValor(const std::vector<Persona> grupo);
        void contarPersonasPorCalendarioPorValor(const std::vector<Persona> personas); 
        void contarPersonaPatrimonioMayor1000MillonesPorValor(const std :: vector <Persona> personas); 

        
        // Variables miembro publicas
        std::vector<Persona*> grupoA;
        std::vector<Persona*> grupoB;
        std::vector<Persona*> grupoC;

        // Variables por valor
        std::vector<Persona> grupoA_val;
        std::vector<Persona> grupoB_val;
        std::vector<Persona> grupoC_val;

};

#endif // BUSCAR_H