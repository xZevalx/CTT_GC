//
// Created by zeval on 01-12-17.
//

#ifndef CTTTOGVC_NODE_H
#define CTTTOGVC_NODE_H

#include <string>
#include "../Colour/Colour.h"
#include "../CTT/Room.h"
#include <cstdlib>

using namespace std;

class Node {
public:
    Colour* colour;
    long weight;
    int degree = 0;
    string course_code;
    int lecture_id;
    string room;

    /**
     * Default constructor
     */
    Node(string c_id, int l_id, int w);

    /**
     * Increase degree by one
     */
    void increase_degree();

    /**
     * Decrease degree by one
     */
    void decrease_degree();

    /**
     * Tries to paint this node with colour @param clr.
     * @return true if was colored, false if it didn't.
     */
    bool paint(Colour * clr);

};


#endif //CTTTOGVC_NODE_H
