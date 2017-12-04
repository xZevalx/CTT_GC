//
// Created by zeval on 02-12-17.
//

#include <random>
#include "Palette.h"

Palette::Palette(int time_periods, int days, int limit) {
    int i, j;
    colours.reserve(time_periods*days);
    for(i=1; i<=time_periods; ++i){
        for(j=1; j<=days;++j){
            Colour * clr = new Colour(i,j,(uint)limit);
            colours.push_back(clr);
        }
    }
}

Colour *Palette::choose_colour(vector<Colour *> *neighbors) {
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0, (int) colours.size()-1);
    if (neighbors->empty()){
        return colours[distribution(generator)];
    }
    if (neighbors->size() == colours.size()){
        return nullptr; // No quedan colores
    }
    Colour * clr = nullptr;
    bool keep_looking = true;
    while(keep_looking){
        clr = colours[distribution(generator)];
        for(int i=0; i<neighbors->size();++i){
            if(neighbors->at(i) == clr){
                break;
            }
            if (i == neighbors->size() - 1){
                keep_looking = false; // El color elegido es distinto al de sus vecinos
            }
        }
    }
    return clr;
}
