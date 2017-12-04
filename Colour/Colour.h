//
// Created by zeval on 01-12-17.
//

#ifndef CTTTOGVC_COLOUR_H
#define CTTTOGVC_COLOUR_H


#include <sys/param.h>

class Colour {
private:
    uint limit;  /* How many times I can can_be_used this colour */

public:
    int time_period_id;
    int day_number; /* L=1, M=2, X=3, J=4, V=5 */

    /**
     * Default constructor
     * @param tp: time period number
     * @param dn: day number
     * @param lt: limit of uses
     */
    Colour(int tp, int dn, uint lt);

    /**
     * Use this colour and decrease limit of uses.
     * @return True if it's used, false if not.
     */
    bool can_be_used();
};


#endif //CTTTOGVC_COLOUR_H
