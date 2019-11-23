#pragma once

#include "Reservation.h"
#include "Room.h"
#include "Hotel.h"
#include "Costumer.h"


struct HotelManager
{
	hotel_t* hotel;
	costumer_t* costumersArr;
	reservation_t* reservationArr;
	int numOfCostumer;
	int numOfReservation;
	int numOfSubString;

}typedef hotelManager_t;

void addCostumers(char* name, char* creditCard, int year, int month, hotelManager_t* hm);

void checkIn(hotelManager_t* hm);

void showHotelStatus(hotelManager_t* hm);

void checkOut(hotelManager_t* hm, int roomNumber);

void printRoom(hotelManager_t* hm, int roomNumber);

void capitalLetter(char* name);

costumer_t* listOfCustomersBySubStringName(hotelManager_t* hm, char* subStr);



