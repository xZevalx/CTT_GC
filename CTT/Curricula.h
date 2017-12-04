//
// Created by zeval on 02-12-17.
//

#ifndef CTTTOGVC_CURRICULA_H
#define CTTTOGVC_CURRICULA_H

#include <string>
#include <vector>

using namespace std;

class Curricula {
public:
    string name;
    vector<string> course_codes;

    Curricula(string name, vector<string> courses);
};


#endif //CTTTOGVC_CURRICULA_H
