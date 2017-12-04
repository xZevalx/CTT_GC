//
// Created by zeval on 01-12-17.
//

#include <iostream>
#include <random>
#include "Graph.h"

Graph::Graph() = default;

void Graph::connect_nodes(string nid_1, string nid_2) {
    // Chequear si ya estan conectados
    auto v = edges_table[nid_1];
    for(const auto& s : v){
        if (s == nid_2){
            return;
        }
    }
    // Si no, conectar
    edges_table[nid_1].push_back(nid_2);
    edges_table[nid_2].push_back(nid_1);
    nodes[nid_1]->increase_degree();
    nodes[nid_2]->increase_degree();
}

string Graph::add_node(Node *n){
    string node_code = n->course_code + '_' + std::to_string(n->lecture_id);
    nodes[node_code] = n;
    return node_code;
}

void Graph::print_edges(){
    for(const auto& n1 : edges_table){
        std::cout << n1.first << ": ";
        for (const auto& n2 : n1.second){
            std::cout << n2 << " ";
        }
        std::cout << '\n';
    }
}

bool Graph::max_weight_neighborhood(string node_name, Node *nodeptr) {
    int degree = nodeptr->degree;
    for (const auto& neighbor : edges_table[node_name]) {
        if(nodes[neighbor]->colour){ // Si el vecino esta pintado lo ignoro
            continue;
        }
        if (degree < nodes[neighbor]->degree){
            return false;
        } else if (degree == nodes[neighbor]->degree && nodeptr->weight < nodes[neighbor]->weight){
            return false;
        }
    }
    return true;
}

void Graph::neighbor_colours(string node_name, vector<Colour*>* container){
    Colour * clr;
    for (const auto& neighbor : edges_table[node_name]){
        clr = nodes[neighbor]->colour;
        if (clr){
            // Chequear q no este el color
            bool esta = false;
            for(int i=0; i<container->size(); ++i){
                if(container->at(i) == clr){
                    esta = true;
                    break;
                }
            }
            if(!esta) {
                container->push_back(clr);
            }
        }
    }
}

void Graph::print_nodes() {
    for(const auto& node : nodes){
        if(node.second->colour){
            std::cout << node.second->course_code << ' '
                      << node.second->colour->day_number << ' '
                      << node.second->colour->time_period_id << ' '
                      << node.second->room << ' '
                      <<  '\n';
        }

    }
    std::cout << std::flush;
}

void build_graph(CTT_Data *data, Graph *g){
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,INT32_MAX);
    // Crear nodos por catedras
    vector<string> node_codes;
    for( const auto& n : data->courses ) {
        int lecture;
        // Crea todas las catedras por curso
        for (lecture=1; lecture<=n.second->get_lectures();++lecture){
            Node * node = new Node(*n.second->get_code(), lecture, distribution(generator));
            node_codes.push_back(g->add_node(node));
        }
        // Agrega arista entre ellos
        for (lecture=0; lecture<n.second->get_lectures() - 1;++lecture){
            int neighbor;
            for (neighbor = lecture + 1; neighbor<n.second->get_lectures();++neighbor){
                g->connect_nodes(node_codes[lecture], node_codes[neighbor]);
            }
        }
        node_codes.clear();
    }
    // Agrega aristas entre nodos con distinto curso y mismo profesor
    for (const auto& n : data->courses_per_teacher){
        int c1, c2;
        string course_code_1, course_code_2;
        // Hay q conectar cada catedra de course_code_1 con cada una de course_code2
        for (c1=0; c1<n.second.size() - 1; ++c1){
            course_code_1 = n.second[c1];
            for (c2 = c1 + 1; c2 < n.second.size() ; ++c2) {
                course_code_2 = n.second[c2];
                connect_nodes(course_code_1, course_code_2,
                              data->courses[course_code_1]->get_lectures(),
                              data->courses[course_code_2]->get_lectures(), g);
            }
        }
    }
    // Agrega aristas entre los cursos q pertenecen a la misma malla
    for (const auto& n : data->curriculas){
        int c1, c2;
        string course_code_1, course_code_2;
        // Hay q conectar cada catedra de course_code_1 con cada una de course_code2
        for (c1=0; c1<n.course_codes.size() - 1; ++c1){
            course_code_1 = n.course_codes[c1];
            for (c2 = c1 + 1; c2 < n.course_codes.size() ; ++c2) {
                course_code_2 = n.course_codes[c2];
                connect_nodes(course_code_1, course_code_2, data->courses[course_code_1]->get_lectures(), data->courses[course_code_2]->get_lectures(), g);
            }
        }
    }
}

void connect_nodes(string code1, string code2, int L1, int L2, Graph *g) {
    string ncode_1, ncode_2;
    int l1, l2;
    for (l1 = 1; l1 <= L1; ++l1) {
        ncode_1 = code1 + '_' + to_string(l1);
        for (l2 = 1; l2 <= L2; ++l2) {
            ncode_2 = code2 + '_' + to_string(l2);
            g->connect_nodes(ncode_1, ncode_2);
        }
    }
}


