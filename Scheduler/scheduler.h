//
// Created by zeval on 04-12-17.
//

#ifndef CTTTOGVC_SCHEDULER_H
#define CTTTOGVC_SCHEDULER_H

#include "../Graph/Graph.h"
#include "../Colour/Palette.h"

void schedule(Graph *g, Palette *p);

void asign_rooms(Graph *g, CTT_Data *data);

#endif //CTTTOGVC_SCHEDULER_H
