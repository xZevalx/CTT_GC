//
// Created by zeval on 01-12-17.
//

#include "Node.h"

Node::Node(string c_id, int l_id, int w) {
    course_code = c_id;
    lecture_id = l_id;
    weight = w;
    colour = nullptr;
}

void Node::increase_degree(){
    ++degree;
}

void Node::decrease_degree(){
    --degree;
}

bool Node::paint(Colour * clr){
    if (clr->can_be_used()){ // can_be_used reduce limite se usos
        colour = clr;
        return true;
    }
    return false;
}
