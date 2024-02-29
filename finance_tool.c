#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <bool.h>

// Primary data object for processing (entry -- instance of spending money) 
// * These are meant to be stored in binary files. This is why the members are as such.
// 	(1) vendor_length tells you how many bytes to read for the vendor's name
// 	(2) vendor_name is the name with which to associate the transaction
// 	(3) 
typedef struct transaction
{
	unsigned short vendor_length;
	char *vendor_name;
	double amount;
	char month[3];
	char day[3];
	char year[5];
} transaction;

transaction* create_transaction(char *vendor_name, double amount, month[], char day[], char year[])
{
	transaction *new_transaction = malloc(sizeof(transaction));
	new_transaction->vendor_length = (unsigned short) strlen(vendor_name) + 1;
	new_transaction->vendor_name = strcpy(vendor_name);
	new_transaction->amount = amount;
	new_transaction->month = strcpy(month);
	new_transaction->day = strcpy(month);
	new_transaction->year = strcpy(year);

	return new_transaction;
}

bool write_transactions(transaction **transactions, int transactions_len, FILE *fh)
{
	for(int i = 0; i < transactions_len; i++)
	{
		fwrite(
	}
}

int main(void)
{

	return 0;
}
