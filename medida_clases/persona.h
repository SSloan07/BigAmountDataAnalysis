#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <iostream>
#include <iomanip>

/**
 * Clase que representa una persona con datos personales y financieros.
 * 
 * POR QUÉ: Para modelar una entidad persona con atributos relevantes para el sistema.
 * CÓMO: Mediante una clase con atributos privados y métodos públicos de acceso y visualización.
 * PARA QUÉ: Centralizar y encapsular la información de una persona, garantizando integridad de datos.
 */
class Persona {
private:
    std::string nombre;           // Nombre de pila
    std::string apellido;         // Apellidos
    std::string id;               // Identificador único (cédula)
    std::string ciudadNacimiento; // Ciudad de nacimiento
    std::string fechaNacimiento;  // Fecha de nacimiento en formato DD/MM/AAAA
    double ingresosAnuales;       // Ingresos anuales en pesos colombianos
    double patrimonio;            // Patrimonio total (activos)
    double deudas;                // Deudas totales (pasivos)
    bool declaranteRenta;         // Si es declarante de renta

public:
    /**
     * Constructor para inicializar todos los atributos de la persona.
     * 
     * POR QUÉ: Necesidad de crear instancias de Persona con todos sus datos.
     * CÓMO: Recibe cada atributo por valor y los mueve a los miembros correspondientes.
     * PARA QUÉ: Construir objetos Persona completos y válidos.
     */
/// 🔹 Constructor por defecto (para usar en std::vector<Persona>(N))
        Persona()
        : nombre(""), apellido(""), id(""), ciudadNacimiento(""), fechaNacimiento(""),
        ingresosAnuales(0.0), patrimonio(0.0), deudas(0.0), declaranteRenta(false) {}

        /// 🔹 Constructor completo con todos los parámetros
        Persona(std::string nom, std::string ape, std::string id, 
            std::string ciudad, std::string fecha, double ingresos, 
            double patri, double deud, bool declara)
        : nombre(nom), apellido(ape), id(id),
        ciudadNacimiento(ciudad), fechaNacimiento(fecha),
        ingresosAnuales(ingresos), patrimonio(patri), deudas(deud), 
        declaranteRenta(declara) {}

    
    // Métodos de acceso (getters) - Implementados inline para eficiencia
    std::string getNombre() const { return nombre; }
    std::string getApellido() const { return apellido; }
    std::string getId() const { return id; }
    std::string getCiudadNacimiento() const { return ciudadNacimiento; }
    std::string getFechaNacimiento() const { return fechaNacimiento; }
    double getIngresosAnuales() const { return ingresosAnuales; }
    double getPatrimonio() const { return patrimonio; }
    double getDeudas() const { return deudas; }
    bool getDeclaranteRenta() const { return declaranteRenta; }

    /**
     * Muestra toda la información de la persona de forma detallada.
     * 
     * POR QUÉ: Para inspeccionar todos los datos de una persona en formato legible.
     * CÓMO: Imprime en la salida estándar con formato.
     * PARA QUÉ: Depuración y visualización completa de un registro.
     */
    void mostrar() const;
    
    /**
     * Muestra un resumen de la persona (ID, nombre, ciudad, ingresos).
     * 
     * POR QUÉ: Para listar personas de forma compacta en listados.
     * CÓMO: Imprime solo los datos más relevantes.
     * PARA QUÉ: Visualización eficiente en colecciones grandes.
     */
    void mostrarResumen() const;
};

#endif // PERSONA_H