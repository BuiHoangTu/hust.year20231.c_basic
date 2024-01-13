//
// Created by tu on 08/01/2024.
//
#include <bits/types/FILE.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "map/hash_map.h"
#include "core/hash.h"

/**
* The data about bank transactions consists of a sequence of transactions: the information of each transaction has the following format:
                                                                    <from_account>   <to_account>   <money>   <time_point>   <atm>
In which:
•	<from_account>: the account from which money is transferred (which is a string of length from 6 to 20 )
•	<to_account>: the account which receives money in the transaction (which is a string of length from 6 to 20)
•	<money>: amount of money transferred in the transaction (which is an integer from 1 to 10000)
•	<time_point>: the time point at which the transaction is performed, it is a string under the format HH:MM:SS  (hour: minute: second)
•	<atm>: the code of the ATM where the transaction is taken (a string of length from 3 to 10)
Example: T00112233445 T001234002 2000 08:36:25 BIDV (at the ATM BIDV, account T00112233445 transfers 2000$ to account T001234002 at time point 08:36:25 (08 hour, 36 minutes, 25 seconds)
A transaction cycle of length k starting from account a1 is defined to be a sequence of distinct account a1, a2, …, ak  in which there are transactions from account a1 to a2, from a2 to a3, …, from ak to a1.
Write a program that process the following queries:
?number_transactions: compute the total number of transactions of the data
?total_money_transaction: compute the total amount of money of transactions
?list_sorted_accounts: compute the sequence of bank accounts (including sending and receiving accounts) appearing in the transaction (sorted in an increasing (alphabetical) order)
?total_money_transaction_from <account>: compute the total amount of money transferred from the account <account>
?inspect_cycle <account> k : return 1 if there is a transaction cycle of length k, starting from <account>, and return 0, otherwise
*/

#define READ_TRANSACTION 1
#define QUERY 2
#define EXIT 0
#define STRTOK_DELIM " \n"

typedef struct {
    char *from;
    char *to;
    int money;
    char *time;
    char *atm;
}Transaction;

int compareTransaction(void *vt1, void *vt2) {
    Transaction *t1 = (Transaction*) vt1;
    Transaction *t2 = (Transaction*) vt2;

    int cmp1 = strcmp(t1->from, t2->from);

    if (cmp1 != 0) return cmp1;

    return strcmp(t1->to, t2->to);
}

int sqortCmp(void *vt1, void *vt2) {
    Transaction *t1 = *((Transaction**) vt1);
    Transaction *t2 = *((Transaction**) vt2);

    int cmp1 = strcmp(t1->from, t2->from);

    if (cmp1 != 0) return cmp1;

    return strcmp(t1->to, t2->to);
}

int main() {
    FILE *input = fopen("./bank_transaction.txt", "r");

    char *line = (char*) malloc(1024 * sizeof(char));
    line[0] = '\0';

    HashMap *cardMap = createHashmap((HashFunction) hashString, (CompareFunction) strcmp);
    ArrayList *transactions = createArraylist();
    int n = 0;
    int totalMoney = 0;

    int mode = READ_TRANSACTION;

    while (mode == READ_TRANSACTION) {
        fgets(line, 1024, input);

        if (strncmp(line, "#", 1) == 0) {
            mode = QUERY;
            break;
        }

        quickCalloc(Transaction, transaction);
        transaction->from = strdup(strtok(line, STRTOK_DELIM));
        transaction->to = strdup(strtok(NULL, STRTOK_DELIM));
        sscanf(strtok(NULL, STRTOK_DELIM),"%d", &(transaction->money));
        transaction->time = strdup(strtok(NULL, STRTOK_DELIM));
        transaction->atm = strdup(strtok(NULL, STRTOK_DELIM));

        n ++;

        totalMoney += transaction->money;

        arraylistAddLast(transactions, transaction);

        void *cardTransactionList = hashmapGet(cardMap, transaction->from);
        if (cardTransactionList) {
            arraylistAddLast(((ArrayList *) cardTransactionList), transaction);
        } else {
            ArrayList *newTransactionList = createArraylist();
            arraylistAddLast(newTransactionList, transaction);
            hashmapPut(cardMap, transaction->from, newTransactionList);
        }
    }

    while (mode == QUERY) {
        fgets(line, 1024, input);

        if (strncmp(line, "#", 1) == 0) {
            mode = EXIT;
            break;
        }

        if (strncmp(line, "?number_transactions", 12) == 0) {
            printf("%d\n", n);
            continue;
        }

        if (strncmp(line, "?total_money_transaction", 12) == 0) {
            printf("%d\n", totalMoney);
            continue;
        }

        if (strncmp(line, "?total_money_transaction_from", 12) == 0) {
            char *fromCard = strtok(line + 30, " \r\n");
            int cardTotal = 0;

            ArrayList *cardTransactionList = (ArrayList*) hashmapGet(cardMap, fromCard);
            for (int i = 0; i < cardTransactionList->length; i++) {
                Transaction *curr = (Transaction*) arraylistGet(cardTransactionList, i);
                cardTotal += curr->money;
            }

            printf("%d\n", cardTotal);

            continue;
        }

        if (strncmp(line, "?inspect_cycle", 12) == 0) {
            printf("%d\n", n);
            continue;
        }


        if (strncmp(line, "?list_sorted_accounts", 12) == 0) {
            qsort(transactions->content, transactions->length, sizeof(void*), sqortCmp);

            printf("transaction sorted");
        }
    }
}