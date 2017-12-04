//
// Created by zeval on 01-12-17.
//

#include "Course.h"

Course::Course(string cd, string tch, uint lts, uint stds){
    code = cd;
    teacher = tch;
    lectures = lts;
    students = stds;
}

string * Course::get_code(){
    return &code;
}

uint Course::get_lectures(){
    return lectures;
}