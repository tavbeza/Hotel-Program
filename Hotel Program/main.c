#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS

#include "HotelManager.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define FALSE 1
#define TRUE 0

void main()
{
	int i, select, creditCardYear, creditCardMonth, leaveRoomNumber, statusNumber;
	char* customerCreditCard;
	char customerName[20];
	costumer_t* subStringCustomerName = NULL;
	hotelManager_t hm;
	hm.costumersArr = (costumer_t*)calloc(1, sizeof(costumer_t));
	hm.reservationArr = (reservation_t*)calloc(1, sizeof(reservation_t));
	hm.hotel = (hotel_t*)calloc(1, sizeof(hotel_t));
	hm.numOfCostumer = 0;
	hm.numOfReservation = 0;
	hm.numOfSubString = 0;

	printf("Welcome to Hotel California!");
	printf("\nPlease enter the number of floors that you want: ");
	scanf("%d", &hm.hotel->numOfFloor);
	printf("\nPlease enter the number of rooms in floor that you want (between 1-100): ");
	scanf("%d", &hm.hotel->numOfRoomPerFloor);

	hm.hotel->rooms = (room_t**)calloc(hm.hotel->numOfFloor*hm.hotel->numOfRoomPerFloor, sizeof(room_t*));
	for (i = 0; i < hm.hotel->numOfFloor; i++)
	{
		hm.hotel->rooms[i] = (room_t*)calloc(hm.hotel->numOfRoomPerFloor, sizeof(room_t));
	}

	do
	{
		printf("Please choose one option:\n1- Add customer\n2- Check in\n3- Hotel status\n4- Check out\n5- Room details\n6- Sub string names\n0- To exit\n");
		scanf_s("%d", &select);
		while (getchar() != '\n')
			flushall();
		switch (select)
		{
		case 1:
			{
			printf("Please enter the customer name: \n");
			scanf("%s", customerName);
			capitalLetter(customerName);
			do
			{
				while (getchar() != '\n');
				customerCreditCard = (char*)calloc(CREDIT_CARD_SIZE, sizeof(int));
				printf("\nPlease enter the credit card number: (12 digits)");
				for (i = 0; i < CREDIT_CARD_SIZE; i++)
				{
					scanf_s("%1d", &customerCreditCard[i]);
				}
			} while (strlen(customerCreditCard) != CREDIT_CARD_SIZE || getchar() != '\n');
			do
			{
				printf("Please enter the credit card year: (between 2010-2020) \n");
				scanf("%d", &creditCardYear);
			} while (!((creditCardYear >= 2010) && (creditCardYear <= 2020)));
			do
			{
				printf("Please enter the credit card month: (between 1-12) \n");
				scanf("%d", &creditCardMonth);

			} while (!((creditCardMonth >= 1) && (creditCardMonth <= 12)));
			addCostumers(customerName, customerCreditCard, creditCardYear, creditCardMonth, &hm);
			printf("The customer create completed!\n");
			break;
		}

		case 2:
		{
			checkIn(&hm);
			break;
		}
		case 3:
		{
			showHotelStatus(&hm);
			break;
		}
		case 4:
		{
			printf("Please enter the room number thet you want you leave:\n");
			scanf("%d", &leaveRoomNumber);
			checkOut(&hm, leaveRoomNumber);
			break;
		}
		case 5: 
		{
			printf("Please enter the room number that you want to see:\n");
			scanf("%d", &statusNumber);
			printRoom(&hm, statusNumber);
			break;
		}
		case 6:
		{
			printf("Please enter sub string: \n");
			scanf("%s", customerName); // I dont have gets() on my computer
			//while (getchar != '\n');
			subStringCustomerName = listOfCustomersBySubStringName(&hm, customerName);
			if (subStringCustomerName[0].month == 0)
			{
				printf("There is no sub string like what you insert.\n");
			}
			else
			{
				printf("The customers names:\n");
				for (i = 0; i < hm.numOfSubString; i++)
				{
					printf("#%d: %s\n", i + 1, subStringCustomerName[i].name);
				}
				free(subStringCustomerName);
				hm.numOfSubString = 0;
			}
			break;
		}

		}

	} while (!(select == 0));
	
	printf("Thank you and have a good day!!\n");

	system("pause");
}