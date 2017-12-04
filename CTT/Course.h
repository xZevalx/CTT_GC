//
// Created by zeval on 01-12-17.
//

#ifndef CTTTOGVC_COURSE_H
#define CTTTOGVC_COURSE_H

using namespace std;

#include <string>
#include "../Colour/Colour.h"

class Course {
private:
    string code;
    string teacher;
    uint lectures;
public:
    uint students;

    /**
     * Default constructor
     * @param cd course code
     * @param tch teacher's name
     * @param lts lectures per week
     * @param stds number of students
     */
    Course(string cd, string tch, uint lts, uint stds);

    string * get_code();

    uint get_lectures();
};


#endif //CTTTOGVC_COURSE_H
