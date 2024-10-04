#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<typename T>
class Par{
public:
    int clave;
    T valor;

    Par(int c, const T& v) : clave(c), valor(v){}
};

template<typename T>
class HashTable{
public:
    HashTable(int tamInicial = 5){
        tabla.resize(tamInicial);
    }
    
    int funcionHash(int clave){
        return clave % tabla.size();
    }
    
    void insertar(int clave, const T& valor){
        int indice = funcionHash(clave);
        for (auto& par : tabla[indice]){
            if (par.clave == clave){
                par.valor = valor;
                return;
            }
        }
        tabla[indice].push_back(Par<T>(clave, valor));
    }

    bool buscar(int clave, T& valorEncontrado){
        int indice = funcionHash(clave);
        for (const auto& par : tabla[indice]){
            if (par.clave == clave){
                valorEncontrado = par.valor;
                return true;
            }
        }
        return false;
    }

    bool eliminar(int clave){
        int indice = funcionHash(clave);
        for (size_t i = 0; i < tabla[indice].size(); ++i){
            if (tabla[indice][i].clave == clave){
                tabla[indice].erase(tabla[indice].begin() + i);
                return true;
            }
        }
        return false;
    }

    void mostrarTabla() const{
        for (size_t i = 0; i < tabla.size(); ++i){
            std::cout<<"Indice "<<i<<": ";
            if (tabla[i].empty()){
                std::cout<<"(vacío)";
            }else{
                for (const auto& par : tabla[i]){
                    std::cout<<"[Clave: "<<par.clave<<", Valor: "<<par.valor<<"] ";
                }
            }
            std::cout<<std::endl;
        }
    }

private:
    vector<vector<Par<T>>> tabla;
};

int main(){
    HashTable<string> tablaHash;

    int opcion, clave;
    string valor;

    do{
        std::cout<<"\n--- Tabla Hash Interactiva ---"<<std::endl;
        std::cout<<"1) Insertar clave-valor"<<std::endl;
        std::cout<<"2) Eliminar por clave"<<std::endl;
        std::cout<<"3) Buscar valor por clave"<<std::endl;
        std::cout<<"4) Mostrar tabla"<<std::endl;
        std::cout<<"5) Salir"<<std::endl;
        std::cout<<"Opcion: ";
        cin >> opcion;

        switch (opcion){
            case 1:
                std::cout<<"Ingresa la clave(int): ";
                cin >> clave;
                std::cout<<"Ingresa el valor(string): ";
                cin.ignore();
                getline(cin, valor);
                tablaHash.insertar(clave, valor);
                std::cout<<"Elemento insertado."<<std::endl;
                break;

            case 2:
                std::cout<<"Ingresa la clave a eliminar: ";
                cin >> clave;
                if (tablaHash.eliminar(clave)){
                    std::cout<<"Clave "<<clave<<" eliminada"<<std::endl;
                }else{
                    std::cout<<"Clave "<<clave<<" no encontrada"<<std::endl;
                }
                break;

            case 3:
                std::cout<<"Clave: ";
                cin >> clave;
                if (tablaHash.buscar(clave, valor)){
                    std::cout<<"Valor encontrado: "<<valor<<std::endl;
                }else{
                    std::cout<<"Clave no encontrada"<<std::endl;
                }
                break;

            case 4:
                std::cout<<"Contenido de la tabla:"<<std::endl;
                tablaHash.mostrarTabla();
                break;

            case 5:
                break;

            default:
                std::cout<<"Opcion invalida"<<std::endl;
        }
    }while (opcion != 5);

    return 0;
}
