#pragma once

#include "Costumer.h"
#include "Room.h"

struct Reservation
{
	costumer_t* costumerList;
	int numOfSleepPeople;
	int numOfBreakfastPeople;
	room_t* room;
	int isCheckOut;
}typedef reservation_t;