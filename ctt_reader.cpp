//
// Created by zeval on 03-12-17.
//

#include "ctt_reader.h"

void read_courses(ifstream *f, unordered_map<string, Course*> *storage,
                  unordered_map<string, vector<string>> *courses_per_tch) {
    string line;
    stringstream ss;
    string cname, cteacher, slectures, sstudents;
    int nlectures, nstudents;
    while (getline(*f,line)){
        if (line.empty()){
            break;
        }
        ss.write(line.c_str(), line.length());
        ss >> cname; ss >> cteacher; ss >> slectures; ss >> sstudents;
        ss.clear();
        nlectures = stoi(slectures);
        nstudents = stoi(sstudents);
        (*storage)[cname] = new Course(cname, cteacher, nlectures, nstudents);
        (*courses_per_tch)[cteacher].push_back(cname);
    }
}

void read_rooms(ifstream *f, vector<Room> *storage){
    string line;
    stringstream ss;
    string rname, capacity;
    int ncapacity;
    while (getline(*f,line)){
        if (line.empty()){
            break;
        }
        ss.write(line.c_str(), line.length());
        ss >> rname; ss >> capacity;
        ss.clear();
        ncapacity = stoi(capacity);
        storage->push_back(Room(rname, ncapacity));
    }
}

void read_curriculas(ifstream *f, vector<Curricula> *storage) {
    string line;
    stringstream ss;
    string curname, str_ncourses, cname;
    int ncourses = -1;
    vector<string> courses_codes;
    while (getline(*f, line)){
        if (line.empty()){
            break;
        }
        ss.write(line.c_str(), line.length());
        ss >> curname; ss >> str_ncourses;
        ncourses = stoi(str_ncourses);
        for (int i = 0; i < ncourses; ++i){
            ss >> cname;
            courses_codes.push_back(cname);
        }
        storage->push_back(Curricula(curname, courses_codes));
        ss.clear();
        courses_codes.clear();
    }
}

int metadata_value(string s){
    ulong j;
    j = s.find(' ');
    return stoi(s.substr(j+1, s.length()));
}

bool starts_with(string s, string prefix){
    if (s.length() < prefix.length()){
        return false;
    }  else if (prefix.length() > 0){
        int i;
        for (i = 0; i<=prefix.length()-1; ++i){
            if (prefix[i] != s[i]){
                return false;
            }
        }
    }
    return true; // All strings have empty character as prefix
}

void read_ctt_file(string path, CTT_Data *data) {
    ifstream ifile;
    ifile.open(path, ios::in);
    string line;
    if (!ifile.is_open()){return;}

    while(getline(ifile, line)){
        string s = string(line);
        if (starts_with(s, "Courses")){
            data->ncourses = metadata_value(s);
        } else if (starts_with(s, "Rooms")) {
            data->nrooms = metadata_value(s);
        } else if (starts_with(s, "Days")) {
            data->days = metadata_value(s);
        } else if (starts_with(s, "Periods_per_day")) {
            data->periods_per_day = metadata_value(s);
        } else if (starts_with(s, "Curricula")) {
            data->curricula = metadata_value(s);
        } else if (starts_with(s, "COURSES")) {
            read_courses(&ifile, &data->courses, &data->courses_per_teacher);
        } else if (starts_with(s, "ROOMS")) {
            read_rooms(&ifile, &data->rooms);
        } else if (starts_with(s, "CURRICULA")) {
            read_curriculas(&ifile, &data->curriculas);
        }
    }
    ifile.close();
}

