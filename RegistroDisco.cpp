#include <iostream>
#include <vector>

using namespace std;

class Registro{
public:
    int identificador;

    Registro(int id) : identificador(id){}
};

class Pagina{
public:
    vector<Registro> listaRegistros;
    const int capacidadMaxima = 4; 

    bool agregarRegistro(const Registro& nuevoRegistro){
        if (listaRegistros.size() < capacidadMaxima){
            listaRegistros.push_back(nuevoRegistro);
            return true;
        }
        return false;
    }

    bool eliminarRegistroPorID(int id){
        for (size_t i = 0; i < listaRegistros.size(); ++i){
            if (listaRegistros[i].identificador == id){
                listaRegistros.erase(listaRegistros.begin() + i);
                return true;
            }
        }
        return false;
    }

    void imprimirRegistros() const{
        if (listaRegistros.empty()){
            std::cout<<" (vacio)";
        }else{
            for (const auto& registro : listaRegistros){
                std::cout<<"ID: "<<registro.identificador<<" ";
            }
        }
    }

    bool existeRegistro(int id) const{
        for (const auto& registro : listaRegistros){
            if (registro.identificador == id){
                return true;
            }
        }
        return false;
    }
};

class Bloque{
public:
    vector<Pagina> paginas;
    const int maxPaginas = 2;

    bool agregarEnPaginaDisponible(const Registro& registro){
        for (auto& pagina : paginas){
            if (pagina.agregarRegistro(registro)){
                return true;
            }
        }
        if (paginas.size() < maxPaginas){
            Pagina nuevaPagina;
            nuevaPagina.agregarRegistro(registro);
            paginas.push_back(nuevaPagina);
            return true;
        }
        return false;
    }

    bool eliminarRegistroPorID(int id){
        for (auto& pagina : paginas){
            if (pagina.eliminarRegistroPorID(id)){
                return true;
            }
        }
        return false;
    }

    void mostrarPaginas() const{
        for (size_t i = 0; i < paginas.size(); ++i){
            std::cout<<"  pagina "<<i + 1<<": ";
            paginas[i].imprimirRegistros();
            std::cout<<std::endl;
        }
    }

    bool existeRegistro(int id) const{
        for (const auto& pagina : paginas){
            if (pagina.existeRegistro(id)){
                return true;
            }
        }
        return false;
    }
};

class Disco{
public:
    vector<Bloque> bloques;

    
    bool insertarNuevoRegistro(int id){
        if (buscarRegistro(id)){
            std::cout<<"Registro repetido "<<id<<std::endl;
            return false;
        }
        Registro nuevoRegistro(id);
        for (auto& bloque : bloques){
            if (bloque.agregarEnPaginaDisponible(nuevoRegistro)){
                return true;
            }
        }
        Bloque nuevoBloque;
        nuevoBloque.agregarEnPaginaDisponible(nuevoRegistro);
        bloques.push_back(nuevoBloque);
        return true;
    }

    bool eliminarRegistro(int id){
        for (auto& bloque : bloques){
            if (bloque.eliminarRegistroPorID(id)){
                return true;
            }
        }
        return false;
    }

    void mostrarContenidoDisco() const{
        if (bloques.empty()){
            std::cout<<"DIsco vacio."<<std::endl;
        }else{
            for (size_t i = 0; i < bloques.size(); ++i){
                std::cout<<"Bloque "<<i + 1<<":"<<std::endl;
                bloques[i].mostrarPaginas();
            }
        }
    }

    bool buscarRegistro(int id) const{
        for (const auto& bloque : bloques){
            if (bloque.existeRegistro(id)){
                return true;
            }
        }
        return false;
    }

    void precargarRegistros(){
        insertarNuevoRegistro(1);
        insertarNuevoRegistro(2);
        insertarNuevoRegistro(3);
        insertarNuevoRegistro(10);
        insertarNuevoRegistro(12);
    }
};

int main(){
    Disco disco;
    disco.precargarRegistros();

    int opcion, id;

    do{
        std::cout<<"\n--- Registro ---"<<std::endl;
        std::cout<<"1) Insertar "<<std::endl;
        std::cout<<"2) Eliminar por ID"<<std::endl;
        std::cout<<"3) Mostrar disco"<<std::endl;
        std::cout<<"4) Salir"<<std::endl;
        std::cout<<"Opcion: ";
        cin>>opcion;

        switch (opcion){
            case 1:
                std::cout<<"Ingrese el nuevo ID: ";
                cin>>id;
                disco.insertarNuevoRegistro(id);
                break;

            case 2:
                std::cout<<"Ingrese el ID da eliminar: ";
                cin>>id;
                if (disco.eliminarRegistro(id)){
                    std::cout<<"Registro con ID "<<id<<" eliminado"<<std::endl;
                }else{
                    std::cout<<"Registro con ID "<<id<<" no encontrado"<<std::endl;
                }
                break;

            case 3:
                std::cout<<"Contenido del disco:"<<std::endl;
                disco.mostrarContenidoDisco();
                break;

            case 4:
                break;

            default:
                std::cout<<"Opcion invalida."<<std::endl;
        }
    }while (opcion != 4);

    return 0;
}
