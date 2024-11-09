#include <iostream>

#include "LoadBalancer.h"

void displayMatrix(vector<vector<int>> &matrix, int numServers) {
    cout << "\nMatriz adyacente ingresada:\n";
    for (int i = 0; i < numServers; ++i) {
        for (int j = 0; j < numServers; ++j) {
            if (matrix[i][j] == INF) {
                cout << "INF ";
            } else {
                cout << matrix[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

vector<vector<int>> createMatrix(int numServers) {

    vector<vector<int>> matrix(numServers, vector<int>(numServers, INF));

    for(int i = 0; i < numServers; i++) {
        matrix[i][i] = 0;
    }

    cout<<"Creando Matriz Ayacente..."<<'\n';
    cout<<"Ingresa el costo entre servidores (Marca con un numero negativo cuando no hay conexion)"<<'\n';
    for (int i = 0; i < numServers; ++i) {
        for (int j = i + 1; j < numServers; ++j) {
            int cost;
            cout << "Costo entre el Servidor [" << i << "] y el Servidor [" << j << "] = ";
            cin >> cost;

            if (cost < 0) {
                matrix[i][j] = INF;
                matrix[j][i] = INF;
            } else {
                matrix[i][j] = cost;
                matrix[j][i] = cost;
            }
        }
    }
    return matrix;
}

vector<vector<int>> createRandomMatrix(int numServers) {
    // Semilla para generar números aleatorios
    srand(static_cast<unsigned int>(time(0)));

    vector<vector<int>> matrix(numServers, vector<int>(numServers, INF));

    // Inicializar la diagonal con 0 (costo entre el mismo servidor)
    for (int i = 0; i < numServers; i++) {
        matrix[i][i] = 0;
    }

    cout<<"Creando Matriz Ayacente..."<<'\n';

    // Generar costes aleatorios entre servidores
    for (int i = 0; i < numServers; ++i) {
        for (int j = i + 1; j < numServers; ++j) {
            int cost = rand() % 10 + 1; // Genera un número aleatorio entre 1 y 10
            matrix[i][j] = cost;
            matrix[j][i] = cost;
        }
    }

    return matrix;
}

int main() {
    int numServers;
    int maxRequest;
    cout<<"Numero de servidores que quiere configurar: ";
    cin>>numServers;
    cout<<"Numero de peeticiones maximas que recibiran los servidores: ";
    cin>>maxRequest;
    cout<<'\n';

    int option;
    cout<<"¿Quieres ingresar los costos de la Matriz? (Seleccione '1' o '2')"<<'\n';
    cout<<"1) Elegir costos de Matriz manualmente"<<'\n';
    cout<<"2) Elegir costos de Matriz aleatoriamente (1 - 10)"<<'\n';
    cout<<"Opcion elegida: ";
    cin>>option;
    cout<<'\n';

    vector<vector<int>> matrix;

    // Crear la matriz adyacente dependiendo de la opción del cliente
    if(option == 1) {
        matrix = createMatrix(numServers);
    } else {
        matrix = createRandomMatrix(numServers);
    }

    // Configuración básica de servidores
    /* vector<vector<int>> matrix1 = {
        {0, 1, 2, INF},
        {1, 0, INF, 3},
        {2, INF, 0, 4},
        {INF, 3, 4, 0}
    }; */

    LoadBalancer lb(numServers, matrix, maxRequest);

    lb.displayServerLoads();
    cout<<'\n';
    lb.distributeRequest(0);
    lb.distributeRequest(0);
    lb.distributeRequest(0); // Intentar exceder la carga máxima y pasa al otro servidor
    cout<<'\n';
    lb.displayServerLoads();
    cout<<'\n';
    lb.completeRequest(1);
    lb.distributeRequest(0);
    cout<<'\n';
    lb.displayServerLoads();

    return 0;
}