//
// Created by zeval on 01-12-17.
//

#include "Colour.h"

Colour::Colour(int tp, int dn, uint lt){
    time_period_id = tp;
    day_number= dn;
    limit = lt;
}

bool Colour::can_be_used(){
    if (limit==0){
        return false;  /*Can't be used anymore */
    }
    --limit;
    return true;
}
