#pragma once
#define CREDIT_CARD_SIZE 12

struct Costumer
{
	int costumerId;
	char* name;
	char creditCard[CREDIT_CARD_SIZE];
	int month;
	int year;
}typedef costumer_t;

