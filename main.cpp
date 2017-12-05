#include <iostream>
#include "Graph/Graph.h"
#include "Colour/Palette.h"
#include "Scheduler/scheduler.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2){
        printf("Usage:\n\t $%s ctt_instance.ctt\n", argv[0]);
        return 1;
    }

    string path = argv[1];

    CTT_Data data;
    std::cout << "Leyendo archivo\n";
    read_ctt_file(path, &data);
    Graph g;
    std::cout << "Construyendo grafo\n";
    build_graph(&data, &g);
    Palette p = Palette(data.periods_per_day, data.days, data.nrooms);
    //g.print_edges();
    std::cout << "Pintando...\n";
    schedule(&g, &p);
    std::cout << "Asignando salas\n";
    asign_rooms(&g, &data);
    fstream scheduling;
    scheduling.open("horario.txt", ios::out);
    g.to_file(&scheduling);
    scheduling.close();
    // g.print_nodes(); // Imprime en la salida estandar
    return 0;
}