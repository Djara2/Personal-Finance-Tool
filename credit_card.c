#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "credit_card.h"

transaction* create_transaction(char vendor_name[], double amount, char month[], char day[], char year[], bool is_paid)
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

credit_card* create_credit_card(char name[], transaction **transactions, double balance, unsigned int max_credit)
{
	credit_card *new_credit_card = malloc(sizeof(credit_card));
	strcpy(new_credit_card->name, name);
	new_credit_card->transactions_len = 0;
	new_credit_card->transactions_max = 128;
	new_credit_card->transactions = malloc(sizeof(transaction*) * 128);
	new_credit_card->balance = balance;
	new_credit_card->max_credit = max_credit;

	return new_credit_card;
}

// (1) Writes an array of transactions to a BINARY file.
// (2) The file format is as follows: 
//     (1) amount of transactions to be read
//     (2) transaction 1
//     (3) transaction 2
//         .
//         .
//         .
//     (4) transaction n
// Double pointer is sufficient (versus triple pointer) because we will not have to reallocate
// the memory for this operation
bool write_transactions(transaction *transactions[], int transactions_len, FILE *fh)
{ 
	// write the number of transactions that will be read in reading this file.
	fwrite(&transactions_len, sizeof(int), 1, fh);

	// write the transactions to the file
	const size_t elements_to_write = 1;
	for(int i = 0; i < transactions_len; i++)
	{
		const size_t elements_written = fwrite(transactions[i], sizeof(transaction), 1, fh);
		// error checking
		if(elements_written != elements_to_write)
		{
			fprintf(stderr, "Failed to write transaction #%d (expected to write size = %zu elements, but wrote %zu instead)\n", i, elements_to_write, elements_written);
			return false;
		}
	}

	return true;
}

// (1) Read transactions from a binary file into an array.
//     This array can then be copied over for a credit
//     card to hold them.
// (2) Triple pointer is required, because it is not known how many will be read. 
//     You can tell once you have read the file; however, you cannot know preemptively. 
//     A way around this is to have the function return the array of transactions, but then
//     you can never resize what has been read.
bool read_transactions(transaction ***transactions, unsigned int *transactions_len, unsigned int *transactions_max, FILE *fh)
{
	// determine required size of the transactions buffer. 
	// The first item in a binary file for storing these transactions 
	// is the number of transactions in the file.
	unsigned int transactions_to_read = 0;
	fread(&transactions_to_read, sizeof(int), 1, fh);

	// ensure sufficient memory to read all the structs
	if( ((*transactions_len) + transactions_to_read) >= (*transactions_max) )
	{
		const size_t new_size =  (*transactions_len) + transactions_to_read;
		(*transactions_max) = new_size;
		(*transactions) = realloc( (*transactions), sizeof(transaction) * (*transactions_max));
		if( (*transactions) == NULL )
		{
			fprintf(stderr, "Failed to allocate more memory for the transactions buffer. Requested new size of %zu.\n", new_size);
			return false;
		}
	}

	const size_t elements_to_read = 1;
	// actually read the transaction into the memory buffer
	for(int i = 0; i < transactions_to_read; i++)
	{
		(*transactions)[i] = malloc(sizeof(transaction));
		const size_t elements_read = fread( (*transactions)[i], sizeof(transaction), 1, fh );

		// ensure the memory was actually read as expected
		if(elements_read != elements_to_read)
		{
			fprintf(stderr, "Failed to read %zu elements for transaction #%d (%zu read instead).\n", elements_to_read, i, elements_read);
			return false;
		}
		(*transactions_len)++;
	}
	return true;
}



































