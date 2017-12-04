//
// Created by zeval on 04-12-17.
//

#include <iostream>
#include "scheduler.h"
#include <omp.h>

void schedule(Graph *g, Palette *p) {
    auto unpainted_nodes = g->nodes;
    vector<pair<string,Node*>> independent_set;

    while (!unpainted_nodes.empty()){
        std::cout << "Quedan "<< unpainted_nodes.size() << " nodos sin pintar\n";
        //std::cout << "\tComputando conjunto independiente\n";
        for(const auto& node: unpainted_nodes){
            /* Se computa un conjunto independiente independent_set = {v tq w(v)>w(u) para todos los vecinos u en
             * unpainted_nodes} Por eso se deben ignorar los ya pintados.
             */
            if (g->max_weight_neighborhood(node.first, node.second)){
                independent_set.emplace_back(node);
            }
        }

        /*
         * Para cada nodo en independent_set se elige un color al azar distinto al de sus vecinos
         */
        //std::cout << "\tPintando conjunto independiente\n";
        #pragma omp parallel
        {
            // Prologo
            vector<Colour*> neighbor_clrs;
            Colour* cur_colour = nullptr;
            bool painted;

            int nthreads = omp_get_num_threads();
            int core_id = omp_get_thread_num();
            int thread_start = ((int)independent_set.size()/nthreads) * core_id;
            int thread_end = ((int)independent_set.size()/nthreads) * (core_id + 1);
            if (core_id == nthreads - 1){
                thread_end = (int) independent_set.size();
            }

            // Real work
            for (int i = thread_start; i < thread_end; ++i) {
                auto node = independent_set[i];
                g->neighbor_colours(node.first, &neighbor_clrs);
                painted = false;
                while (!painted) {
                    // Debe ser aleatorio
                    cur_colour = p->choose_colour(&neighbor_clrs);
                    if (cur_colour) {
                        painted = g->nodes[node.first]->paint(cur_colour);
                        if (!painted) {
                            neighbor_clrs.push_back(cur_colour); // Cur_color no puede ser usado mas veces. Forzar otro
                        }
                    } else {
                        painted = true;
                        auto *uncolored = new Colour(-1, -1, 1);
                        g->nodes[node.first]->paint(uncolored);
                    }
                }
                neighbor_clrs.clear();
                /*
                 * Para luego asignar salas
                 */
                if (cur_colour) {
                    #pragma omp critical
                    g->nodes_per_color[cur_colour].push_back(node.first);
                }
            }
        }
        /*
         * unpainted_nodes = unpainted_nodes - independent_set
         */
        //std::cout << "\tSacando nodos pintados\n";
        for(const auto& p : independent_set){
            unpainted_nodes.erase(p.first);
        }
        independent_set.clear();
    }
}

void asign_rooms(Graph *g, CTT_Data *data){
    // Asignar salas
    for(auto& p : g->nodes_per_color){
        vector<Room> rooms_copy = data->rooms;
        for (auto& node : p.second) {
            uint students = data->courses[g->nodes[node]->course_code]->students;
            Room * candidate_room = nullptr;
            int standing_students = INT32_MAX;
            bool is_room_asigned = false;
            int room_idx;
            for(room_idx=0;room_idx < rooms_copy.size(); ++room_idx){
                if (rooms_copy[room_idx].capacity >= students){
                    g->nodes[node]->room = rooms_copy[room_idx].name;
                    is_room_asigned = true;
                    break;
                } else {
                    int diff = students - rooms_copy[room_idx].capacity;
                    if (diff < standing_students){
                        candidate_room = &rooms_copy[room_idx];
                        standing_students = diff;
                    }
                }
            }
            if (!is_room_asigned){
                g->nodes[node]->room = candidate_room->name;
            }
            rooms_copy.erase(rooms_copy.begin() + room_idx);
        }
    }
}
