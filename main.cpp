#include <iostream>
#include "Graph/Graph.h"
#include "Colour/Palette.h"
#include "Scheduler/scheduler.h"

using namespace std;

int main() {
    CTT_Data data;
    std::cout << "Leyendo archivo\n";
    read_ctt_file("../DDS1.ctt", &data);
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
    scheduling.open("../horario.txt", ios::out);
    g.to_file(&scheduling);
    scheduling.close();
    // g.print_nodes(); // Imprime en la salida estandar
    return 0;
}