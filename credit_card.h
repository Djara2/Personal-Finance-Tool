#ifndef CREDIT_CARD_H
#define CREDIT_CARD_H

// Primary data object for processing (entry -- instance of spending money) 
// * These are meant to be stored in binary files. This is why the members are as such.
// 	(1) vendor_length tells you how many bytes to read for the vendor's name
// 	(2) vendor_name is the name with which to associate the transaction
// 	(3) 
typedef struct transaction
{
	unsigned short vendor_length;
	char vendor_name[64];
	double amount;
	char month[3];
	char day[3];
	char year[5];
	bool is_paid;
} transaction;

typedef struct credit_card
{
	char name[64];
	unsigned int transactions_len;
	unsigned int transactions_max;
	transaction **transactions;
	double balance;
	unsigned int max_credit;
} credit_card;

transaction* create_transaction(char vendor_name[], double amount, month[], char day[], char year[]);

credit_card* create_credit_card(char name[], transaction **transactions, double balance, unsigned int max_credit);

// Writes an array of transactions to a binary file.
bool write_transactions(transaction **transactions, int transactions_len, FILE *fh);

void read_transactions(transaction ***transactions, unsigned int *transactions_len, unsigned int *transactions_max);
#endif
