#include "persona.h"
#include <iomanip> // Para std::setprecision

/**
 * Implementación del constructor de Persona.
 * 
 * POR QUÉ: Inicializar los miembros de la clase.
 * CÓMO: Usando la lista de inicialización y moviendo los strings para evitar copias.
 * PARA QUÉ: Eficiencia y correcta construcción del objeto.
 */
Persona::Persona(std::string nom, std::string ape, std::string id, 
                 std::string ciudad, std::string fecha, double ingresos, 
                 double patri, double deud, bool declara)
    : nombre(std::move(nom)), 
      apellido(std::move(ape)), 
      id(std::move(id)), 
      ciudadNacimiento(std::move(ciudad)),
      fechaNacimiento(std::move(fecha)), 
      ingresosAnuales(ingresos), 
      patrimonio(patri),
      deudas(deud), 
      declaranteRenta(declara) {}

/**
 * Implementación de mostrar.
 * 
 * POR QUÉ: Mostrar todos los datos de la persona de forma estructurada.
 * CÓMO: Usando flujos de salida y formateadores.
 * PARA QUÉ: Facilitar la lectura de los datos completos de una persona.
 */
void Persona::mostrar() const {
    std::cout << "-------------------------------------\n";
    std::cout << "[" << id << "] Nombre: " << nombre << " " << apellido << "\n";
    std::cout << "   - Ciudad de nacimiento: " << ciudadNacimiento << "\n";
    std::cout << "   - Fecha de nacimiento: " << fechaNacimiento << "\n\n";
    std::cout << std::fixed << std::setprecision(2); // Formato de números
    std::cout << "   - Ingresos anuales: $" << ingresosAnuales << "\n";
    std::cout << "   - Patrimonio: $" << patrimonio << "\n";
    std::cout << "   - Deudas: $" << deudas << "\n";
    std::cout << "   - Declarante de renta: " << (declaranteRenta ? "Sí" : "No") << "\n";
}

/**
 * Implementación de mostrarResumen.
 * 
 * POR QUÉ: Mostrar información esencial de la persona en una sola línea.
 * CÓMO: Imprime ID, nombre completo, ciudad e ingresos.
 * PARA QUÉ: Listados rápidos y eficientes.
 */
void Persona::mostrarResumen() const {
    std::cout << "[" << id << "] " << nombre << " " << apellido
              << " | " << ciudadNacimiento 
              << " | $" << std::fixed << std::setprecision(2) << ingresosAnuales;
}

/** 
void Persona::edadActual(Persona &persona , int &id) const 
{
    //Comparar el año
    if( (std::stoi(persona.getFechaNacimiento().substr(0 , persona.getFechaNacimiento().find("/"))) < (std::stoi(fechaNacimiento.substr(0, fechaNacimiento.find("/")))))) 
    {
        return;
    }

    //Comparar mes
    if( (std::stoi(persona.getFechaNacimiento().substr(persona.getFechaNacimiento().find('/') + 1, persona.getFechaNacimiento().find('/', persona.getFechaNacimiento().find('/') + 1) - (persona.getFechaNacimiento().find('/') + 1))) < (std::stoi(fechaNacimiento.substr(fechaNacimiento.find('/') + 1, fechaNacimiento.find('/', fechaNacimiento.find('/') + 1) - (fechaNacimiento.find('/') + 1)))))) 
    {
        edadPersona = id; 
        return;
    }

    if( (std::stoi(persona.getFechaNacimiento().substr(persona.getFechaNacimiento().rfind('/') + 1)) < (std::stoi(fechaNacimiento.substr(fechaNacimiento.rfind('/') + 1))))) 
    {
        edadPersona = id; 
        return;
    }
}
*/

const double& Persona :: getPatrimonio() const {
    return patrimonio; 
}
const std::string& Persona :: getCiudadNacimiento () const {
    return ciudadNacimiento; 
}
const std::string& Persona :: getId () const {
    return id; 
}