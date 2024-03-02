#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../credit_card.h"

int main(void)
{
	transaction *transactions[5];
	transactions[0] = create_transaction("Amazon", 16.72, "03", "01", "2024", true);
	transactions[1] = create_transaction("Marcos", 21.84, "03", "01", "2024", true);
	transactions[2] = create_transaction("Amazon", 23.40, "03", "02", "2024", true);
	transactions[3] = create_transaction("Cash App", 5.03, "03", "02", "2024", false);
	transactions[4] = create_transaction("World of Warcraft", 20.00, "03", "02", "2024", true);
	
	FILE *fh = fopen("dummy_data.bin", "wb");
	bool write_status = write_transactions(transactions, 5, fh);
	if(!write_status)
	{
		fprintf(stderr, "Write status for operation write_transactions() failed.\n");
		// free used memory
		for(int i = 0; i < 5; i++)
			free(transactions[i]);

		fclose(fh);
		return 1;
	}
	fclose(fh);

	printf("Successfully wrote 5 files.\n");

	transaction **fetched_transactions = malloc(sizeof(transaction) * 2);
	unsigned int transactions_len = 0;
	unsigned int transactions_max = 2;

	fh = fopen("dummy_data.bin", "rb");
	bool read_status = read_transactions(&fetched_transactions, &transactions_len, &transactions_max, fh);
	if(read_status != true)
	{
		fprintf(stderr, "Read status operation for read_transactions() failed.\n");
		for(int i = 0; i < transactions_len; i++)
			free(fetched_transactions[i]);
		fclose(fh);
		return 1;
	}

	printf("Successfuly read 5 files.\n");
	fclose(fh);

	// display read files
	for(int i = 0; i < 5; i++)
	{
		printf("Transaction %d\n", i);
		printf("\tVendor: %s\n", fetched_transactions[i]->vendor_name);
		printf("\tAmount: %f\n", fetched_transactions[i]->amount);
		printf("\tDate: %s/%s/%s (MM-DD-YYYY)\n", fetched_transactions[i]->month, transactions[i]->day, transactions[i]->year);
		printf("\tPaid: %d\n\n", fetched_transactions[i]->is_paid);
	}

	// free memory
	for(int i = 0; i < 5; i++)
	{
		free(transactions[i]);
		free(fetched_transactions[i]);
	}
	free(fetched_transactions);

	return 0;
}
