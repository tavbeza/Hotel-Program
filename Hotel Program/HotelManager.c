#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#include "HotelManager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define FALSE 1
#define TRUE 0
#define MAX_NAME 20

void capitalLetter(char* name)
{
	if (*name >= 'a' && *name <= 'z')
	{
		*name -= 32;
	}
}

costumer_t* listOfCustomersBySubStringName(hotelManager_t* hm , char* subStr)
{
	int i;
	costumer_t* subStringCustomerList;
	subStringCustomerList = (costumer_t*)calloc(1, sizeof(costumer_t));
	
	for (i = 0; i < hm->numOfCostumer; i++)
	{
		if (strstr(hm->costumersArr[i].name, subStr) != NULL)
		{
			subStringCustomerList[hm->numOfSubString++] = hm->costumersArr[i];
			subStringCustomerList = (costumer_t*)realloc(subStringCustomerList, sizeof(costumer_t)*(hm->numOfSubString+1));
			if (!subStringCustomerList)
				printf("ERROR! Not enough memory!\n");
		}
	}
	return subStringCustomerList;
}

void addCostumers(char* name, char* creditCard, int year, int month , hotelManager_t* hm )
{
	int i;
	if (hm->numOfCostumer != 0)
		hm->costumersArr = (costumer_t*)realloc(hm->costumersArr , sizeof(costumer_t)*(hm->numOfCostumer+1));

	if (!hm->costumersArr)
	{
		printf("ERROR! Not enough memory!\n");
	}
	
	(hm->costumersArr[hm->numOfCostumer]).name = (char*)malloc(strlen(name) + 1);
	strcpy((hm->costumersArr[hm->numOfCostumer]).name, name);
	for (i=0 ; i<CREDIT_CARD_SIZE ; i++)
		(hm->costumersArr[hm->numOfCostumer]).creditCard[i]  = creditCard[i];
	(hm->costumersArr[hm->numOfCostumer]).year = year;
	(hm->costumersArr[hm->numOfCostumer]).month = month;
	(hm->costumersArr[hm->numOfCostumer]).costumerId = (hm->numOfCostumer + 1);

	hm->numOfCostumer++;
}


void checkIn(hotelManager_t* hm)
{
	int i, j, newYear, newMonth;
	char* newCreditCard;// [CREDIT_CARD_SIZE];
	char ch;
	char newName[MAX_NAME];
	
	if (hm->numOfReservation < hm->hotel->numOfRoomPerFloor*hm->hotel->numOfFloor)
	{
		if (hm->numOfReservation != 0)
		{
			hm->reservationArr = (reservation_t*)realloc(hm->reservationArr, sizeof(reservation_t)*(hm->numOfReservation + 1));
		}

		if (!hm->reservationArr)
		{
			printf("ERROR! Not enough memory!\n");
		}

		printf("\nName of the customers is:\n");
		for (i = 0 ; i < hm->numOfCostumer ; i ++)
		{
			printf("#%d: %s \n", (i+1) , hm->costumersArr[i].name);
		}

		printf("Did you see the costumer that you want to checkIn? (Y/N)  \n");
		ch = getchar();
		flushall();
		if (ch == 'Y' || ch == 'y')
		{
			printf("\nPlease enter the number of costumer that you want to choose: ");
			scanf_s("%d", &i);
			printf("\nThe costumer that you chose is: %s", hm->costumersArr[i - 1].name);

			hm->reservationArr[hm->numOfReservation].costumerList = &hm->costumersArr[i - 1];
		}
		else if (ch == 'N' || ch == 'n')
		{
			printf("\nOK, we will create a new costumer.\nPlease enter the name: ");
			scanf("%s", newName); // I I dont have gets() on my computer
			flushall();
			capitalLetter(newName);
			do
			{
				while (getchar() != '\n');
				newCreditCard = (char*)calloc(CREDIT_CARD_SIZE, sizeof(int));
				printf("\nPlease enter the credit card number: (12 digits)");
				for (i = 0; i < CREDIT_CARD_SIZE; i++)
				{
					scanf_s("%1d", &newCreditCard[i]);
				}
			} while (strlen(newCreditCard) != CREDIT_CARD_SIZE || getchar() != '\n');
			do
			{
				printf("\nPlease enter the year of credit card(between 2010-2020):  ");
				scanf_s("%d", &newYear);
			} while (newYear < 2010 || newYear>2020);
			do
			{
				printf("\nPlease enter the month of credit card: ");
				scanf_s("%d", &newMonth);
			} while (newMonth < 1 || newMonth>12);

			addCostumers(newName, newCreditCard, newYear, newMonth, hm);
			hm->reservationArr[hm->numOfReservation].costumerList = &hm->costumersArr[hm->numOfCostumer - 1];
		}
		printf("\nPlease enter the number of people that will stay to sleep: (0-4)  ");
		scanf_s("%d", &hm->reservationArr[hm->numOfReservation].numOfSleepPeople);
		printf("\nPlease enter the number of people that will eat breakfast: (0-%d)  " , hm->reservationArr[hm->numOfReservation].numOfSleepPeople);
		scanf_s("%d", &hm->reservationArr[hm->numOfReservation].numOfBreakfastPeople);

		for (i = 0; i < hm->hotel->numOfFloor ; i++)
			{
			for (j = 0; j < hm->hotel->numOfRoomPerFloor; j++)
			{
				if (hm->hotel->rooms[i][j].availableRoom == TRUE)
				{
					hm->hotel->rooms[i][j].numOfPerson = hm->reservationArr[hm->numOfReservation].numOfSleepPeople;
					hm->hotel->rooms[i][j].numOfPersonRegisteredBreakfast = hm->reservationArr[hm->numOfReservation].numOfBreakfastPeople;
					hm->reservationArr[hm->numOfReservation].isCheckOut = FALSE;
					break;
				}
			}
			if (hm->hotel->rooms[i][j].availableRoom == TRUE)
			{
				hm->hotel->rooms[i][j].availableRoom = FALSE;
				break;
			}
			}
		printf("\nThe reservation completed, thank you!");

		hm->numOfReservation++;
	}
	else
	{
		printf("There is no place, sorry.");
	}
	while (getchar() != '\n');
}


void showHotelStatus(hotelManager_t* hm)
{
	int i, j;

	for (i = 0; i < hm->hotel->numOfFloor; i++)
	{
		for (j = 0; j < hm->hotel->numOfRoomPerFloor; j++)
		{
			if (j < 10)
			{
				if (hm->hotel->rooms[i][j].availableRoom == FALSE)
				{
					printf("\nRoom %d0%d:\nDon't available\nNumber of pepole that sleep: %d\nNumber of people that eat breakfast: %d\n",
						i, j, hm->hotel->rooms[i][j].numOfPerson, hm->hotel->rooms[i][j].numOfPersonRegisteredBreakfast);
				}
				else
				{
					printf("Room %d0%d available.\n" ,i, j);
				}
			}
			else
			{
				if (hm->hotel->rooms[i][j].availableRoom == FALSE)
				{
					printf("\nRoom %d%d:\nDon't available\nNumber of pepole that sleep: %d\nNumber of people that eat breakfast: %d\n",
						i, j,hm->hotel->rooms[i][j].numOfPerson, hm->hotel->rooms[i][j].numOfPersonRegisteredBreakfast);
				}
				else
				{
					printf("Room %d%d available.\n", i, j);
				}
			}
		}
	}
}


void checkOut(hotelManager_t* hm , int roomNumber)
{
	int floorNumber = roomNumber / 100, i;
	int room = roomNumber%100;

	hm->hotel->rooms[floorNumber][room].availableRoom = TRUE;
	hm->hotel->rooms[floorNumber][room].numOfPerson = 0;
	hm->hotel->rooms[floorNumber][room].numOfPersonRegisteredBreakfast = 0;

	for (i = 0; i < hm->numOfReservation; i++)
	{
		if (&hm->reservationArr[i].room == &hm->hotel->rooms[floorNumber][room])
		{
			hm->reservationArr[i].room->availableRoom = TRUE;
		}
	}

}


void printRoom(hotelManager_t* hm, int roomNumber)
{
	int floorNumber = roomNumber / 100;
	int room = roomNumber % 100;


	printf("Room %d:\n", roomNumber);
	if (hm->hotel->rooms[floorNumber][room].availableRoom == TRUE)
		printf("Is available\n");
	else
		printf("Is not available\n");
	printf("Number of person: %d\n", hm->hotel->rooms[floorNumber][room].numOfPerson);
	printf("Number of person the register to breakfast: %d\n", hm->hotel->rooms[floorNumber][room].numOfPersonRegisteredBreakfast);
}

