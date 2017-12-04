//
// Created by zeval on 01-12-17.
//

#ifndef CTTTOGVC_GRAPH_H
#define CTTTOGVC_GRAPH_H

#include <vector>
#include <unordered_map>
#include "Node.h"
#include "../ctt_reader.h"

using namespace std;

class Graph {
public:
    unordered_map<string, Node*> nodes;
    unordered_map<string, vector<string>> edges_table;
    unordered_map<Colour *, vector<string>> nodes_per_color;
    unordered_map<string, vector<Colour *>> colours_per_course;

    Graph();

    void connect_nodes(string nid_1, string nid_2);

    string add_node(Node *n);

    void print_edges();

    void print_nodes();

    bool max_weight_neighborhood(string node_name, Node *nodeptr);

    void neighbor_colours(string node_name, vector<Colour*>* container);

};

void build_graph(CTT_Data *data, Graph *g);

void connect_nodes(string code1, string code2, int L1, int L2, Graph *g);

#endif //CTTTOGVC_GRAPH_H
