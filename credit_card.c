#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "credit_card.h"

transaction* create_transaction(char vendor_name[], double amount, month[], char day[], char year[], bool is_paid)
{
	transaction *new_transaction = malloc(sizeof(transaction));
	strcpy(new_transaction->vendor_name, vendor_name);
	new_transaction->amount = amount;
	strcpy(new_transaction->month, month);
	strcpy(new_transaction->day, day);
	strcpy(new_transaction->year, year);
	new_transaction->is_paid = is_paid;

	return new_transaction;
}

credit_card* create_credit_card(char name[], transaction **transactions, double balance, unsigned int max_credit);

// Writes an array of transactions to a binary file.
bool write_transactions(transaction **transactions, int transactions_len, FILE *fh);

void read_transactions(transaction ***transactions, unsigned int *transactions_len, unsigned int *transactions_max);
#endif
