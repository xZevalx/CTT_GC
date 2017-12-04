//
// Created by zeval on 02-12-17.
//

#ifndef CTTTOGVC_COLOURFACTORY_H
#define CTTTOGVC_COLOURFACTORY_H

#include <vector>
#include "Colour.h"

using namespace std;

class Palette {
private:
    vector<Colour*> colours;
public:
    Palette(int time_periods, int days, int limit);

    Colour *choose_colour(vector<Colour *> *neighbors);
};


#endif //CTTTOGVC_COLOURFACTORY_H
