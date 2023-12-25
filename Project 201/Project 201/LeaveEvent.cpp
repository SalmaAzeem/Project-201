#include "LeaveEvent.h"
#include "Passenger.h"
#include "Station.h"
#include <iostream>
using namespace std;

LeaveEvent::LeaveEvent(char et, int h, int m, int s, int i, int ss) {
	event_type = et;
	hour = h;
	minute = m;
	second = s;
	id = i;
	sstation = ss;
}

void LeaveEvent::execute(Station** array) {
	Passenger* one = new Passenger(id, sstation);
	cout << "id is " << id << endl
		<< "start station is " << sstation << endl

		<< "Hour is: " << hour << std::endl
		<< "Minute is: " << minute << std::endl

		<< '\n';
	array[one->getArrivalStationId()]->Leave_Station(one);
	
	return;
}