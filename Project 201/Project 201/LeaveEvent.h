#pragma once
#include "Event.h"
#include <iostream>

#ifndef LEAVEEVENT_H
#define LEAVEEVENT_H
using namespace std;

class LeaveEvent : public Event
{
public:
	LeaveEvent(char et, int h, int m, int s, int i, int ss);
	Passenger* execute();

};
#endif
