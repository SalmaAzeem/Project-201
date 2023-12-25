#pragma once
#include "Event.h"
#include <iostream>
#include "Station.h"

#ifndef LEAVEEVENT_H
#define LEAVEEVENT_H
using namespace std;

class LeaveEvent : public Event
{
public:
	LeaveEvent(char et, int h, int m, int s, int i, int ss);
	void execute(Station** array);

};
#endif
