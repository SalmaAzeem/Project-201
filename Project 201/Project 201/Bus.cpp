#include "Bus.h"

Bus::Bus(int new_capacity, char new_type, int new_bus_number)
{
	capacity = new_capacity;
	time_mentainance = 0;
	num_journey = 0;
	type = new_type;
	bus_number = new_bus_number;
	count_inside = 0;
	current_station = 0;
	next_station = 0;
	reverse = false;
	timer = 0;
	status = 'E';
}

void Bus::set_bus_id(int new_id)
{
	bus_number = new_id;
}

bool Bus::Move_Bus(bool reverse)
{
	if (!reverse&&status == 'E')
	{
		next_station++;
		status = 'B';
	}
	else
	{
		next_station--;
		status = 'B';

	}
	return true;
}

bool Bus::Is_Full()
{
	if (capacity == count_inside)
	{
		status = 'B';
		return true;
	}
	status = 'E';
	return false;
}


bool Bus::Add_Passenger(Passenger* passenger,char direction)
{
	if ( direction == 'F')
	{
		Bus_passengers.InsertSorted(passenger);  //forward sort asc
		count_inside++;
		return true;
	}
	else if ( direction == 'B')
	{
		Bus_passengers.InsertSortedDesc(passenger);  //backward sort desc
		count_inside++;
		return true;
	}
	return false;
}

int Bus::getId() const {
	return bus_number;
}

//
//bool Bus::Add_Time(int time)
//{
//	if (timer == time)
//	{
//		current_station = next_station;
//		timer = 0;
//		return true;
//	}
//	timer++;
//	return false;
//}

Passenger* Bus::Remove_Passenger(int station_num)
{
	cout << station_num;
	Node<Passenger*>* ptr = Bus_passengers.gethead();
	if(ptr != nullptr )
	{
		if (station_num == ptr->getvalue()->getLeaveStationId())
		{
			Bus_passengers.DeleteNode(ptr->getvalue());
			count_inside--;
			status = 'E';
			cout << ptr->getvalue()->getId();
		//// to remove only one person
		}
	}
	if (ptr == nullptr) return nullptr; /// handle null ptr as it errors with get value when nothing to remove
	return ptr->getvalue();


}

bool Bus::Reverse_Bus(int station, int num_of_journies, int time)
{
	if (current_station == station)
	{
		reverse = true;
		num_journey++;
		return Mentain(num_of_journies, time);
	}
	else if (current_station == 1)
	{
		reverse = false;
		num_journey++;
		return Mentain(num_of_journies, time);
	}
	return false;

}

bool Bus::Mentain(int num_of_journies, int time)
{
	if (num_journey == num_of_journies)
	{
		current_station = next_station = 0;
		status = 'B';
		if (Get_out_of_Mentainance(time))
		{
			status = 'E';
		}
		time_mentainance++;
		return true;
	}
	return false;
}

bool Bus::Get_out_of_Mentainance(int time)
{
	if (time_mentainance == time)
	{
		num_journey = 0;
		return true;
	}
	return false;
}

char Bus::GetType()
{
	return type;
}

bool Bus::get_reverse() const { return reverse; }

bool Bus::Is_Busy()
{
	return status == 'B';
}

int Bus::get_capacity() const { return capacity; }
