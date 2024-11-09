#include "LoadBalancer.h"

using namespace std;

LoadBalancer::LoadBalancer(int n, const vector<vector<int> > &matrix, int maxRequest)
: numServers(n), adjMatrix(matrix), requestsPerServer(n, 0), maxRequest(maxRequest){};


int LoadBalancer::distributeRequest(int startServer) {
    int minCost = INF;
    int selectedServer = -1 ;

    for (int i = 0; i < numServers; ++i) {
        // No se asignan solicitudes al mismo servidor de inicio y solo se consideran los servidores con conexión
        if (i != startServer && adjMatrix[startServer][i] != INF) {
            // Solo consideramos servidores que no hayan alcanzado el límite de solicitudes
            if (requestsPerServer[i] < maxRequest) {
                // Si el servidor tiene un costo menor o igual que el servidor previamente seleccionado
                // y tiene menos solicitudes activas, se selecciona
                if ((adjMatrix[startServer][i] < minCost) || 
                    (adjMatrix[startServer][i] == minCost && requestsPerServer[i] < requestsPerServer[selectedServer])) {
                    minCost = adjMatrix[startServer][i];
                    selectedServer = i;
                }
            }
        }
    }

    if (selectedServer != -1) {
        requestsPerServer[selectedServer]++;
        cout << "Solicitud asignada al Servidor " << selectedServer
                  << " desde Servidor " << startServer << ", Carga actual: "
                  << requestsPerServer[selectedServer] << "\n";
    } else {
        cout << "No hay servidores disponibles desde el Servidor " << startServer << "\n";
    }
    return selectedServer;

}

void LoadBalancer::completeRequest(int serverId) {
    // Se valida que el servidor exista y que exista dentro de los servidores inicializados
    // o que el servidor tenga al menos 1 solicitud
    if(serverId < 0 || serverId >= numServers || requestsPerServer[serverId] == 0) {
        cout << "Error: no hay solicitudes activas en el Servidor " << serverId << "\n";
        return;
    }

    requestsPerServer[serverId]--;
    std::cout << "Solicitud completada en el Servidor " << serverId
             << ", Carga actual: " << requestsPerServer[serverId] << "\n";
}

void LoadBalancer::displayServerLoads() {
    std::cout << "Cargas actuales de los servidores:\n";
    for (int i = 0; i < numServers; ++i) {
        std::cout << "Servidor " << i << ": " << requestsPerServer[i] << " solicitudes\n";
    }
}