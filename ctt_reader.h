//
// Created by zeval on 03-12-17.
//

#ifndef CTTTOGVC_CTT_READER_H
#define CTTTOGVC_CTT_READER_H

#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "CTT/Course.h"
#include "CTT/Room.h"
#include "CTT/Curricula.h"

using namespace std;

class CTT_Data{
public:
    int ncourses;
    int nrooms;
    int days;
    int periods_per_day;
    int ncurriculas;
    unordered_map<string, Course*> courses;
    vector<Room> rooms;
    vector<Curricula> curriculas;
    unordered_map<string, vector<string>> courses_per_teacher;
};

void read_ctt_file(string path, CTT_Data *data);

bool starts_with(string s, string prefix);

int metadata_value(string s);

void read_courses(ifstream *f, unordered_map<string, Course> *storage,
                  unordered_map<string, vector<string>> *courses_per_tch);

void read_rooms(ifstream *f, vector<Room> *storage, int nrooms);

void read_curriculas(ifstream *f, vector<Curricula> *storage, int ncurriculas);

#endif //CTTTOGVC_CTT_READER_H
