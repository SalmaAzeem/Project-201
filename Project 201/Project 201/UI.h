#pragma once
#ifndef UI_H
#define UI_H
#include <iostream>
#include "Station.h"
#include "Passenger.h"
#include "Bus.h"


class UI {
public:
	UI() {};
	void interface(Station** array, int num) const;
};
#endif