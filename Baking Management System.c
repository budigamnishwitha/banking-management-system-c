#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int acc_no;
    char name[50];
    float balance;
};

// ? Check if account exists
int isAccountExists(int acc_no) {
    struct Account a;
    FILE *fp = fopen("accounts.dat", "rb");

    if (fp == NULL) return 0;

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc_no) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ? Create Account
void createAccount() {
    struct Account a;
    FILE *fp = fopen("accounts.dat", "ab");

    if (fp == NULL) {
        printf("File error!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &a.acc_no);

    if (isAccountExists(a.acc_no)) {
        printf("Account already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf(" %49[^\n]", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);

    printf("? Account created successfully!\n");
}

// ? Display Accounts
void displayAccounts() {
    struct Account a;
    FILE *fp = fopen("accounts.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n===== ACCOUNT LIST =====\n");

    while (fread(&a, sizeof(a), 1, fp)) {
        printf("\nAcc No: %d\nName: %s\nBalance: %.2f\n", a.acc_no, a.name, a.balance);
    }

    fclose(fp);
}

// ? Deposit
void deposit() {
    int acc, found = 0;
    float amt;
    struct Account a;
    FILE *fp = fopen("accounts.dat", "rb+");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc) {
            found = 1;

            printf("Previous Balance: %.2f\n", a.balance);

            printf("Enter amount to deposit: ");
            scanf("%f", &amt);

            if (amt <= 0) {
                printf("Invalid amount!\n");
                break;
            }

            a.balance += amt;

            fseek(fp, -sizeof(a), SEEK_CUR);
            fwrite(&a, sizeof(a), 1, fp);

            printf("? Amount deposited successfully!\n");
            printf("Current Balance: %.2f\n", a.balance);
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

// ? Withdraw
void withdraw() {
    int acc, found = 0;
    float amt;
    struct Account a;
    FILE *fp = fopen("accounts.dat", "rb+");

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc) {
            found = 1;

            printf("Previous Balance: %.2f\n", a.balance);

            printf("Enter amount to withdraw: ");
            scanf("%f", &amt);

            if (amt <= 0) {
                printf("Invalid amount!\n");
                break;
            }

            if (amt > a.balance) {
                printf("? Insufficient balance!\n");
            } else {
                a.balance -= amt;

                fseek(fp, -sizeof(a), SEEK_CUR);
                fwrite(&a, sizeof(a), 1, fp);

                printf("? Withdrawal successful!\n");
                printf("Remaining Balance: %.2f\n", a.balance);
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(fp);
}

// ? Search Account
void searchAccount() {
    int acc, found = 0;
    struct Account a;
    FILE *fp = fopen("accounts.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%d", &acc);

    while (fread(&a, sizeof(a), 1, fp)) {
        if (a.acc_no == acc) {
            printf("\n? Account Found!\n");
            printf("Name: %s\nBalance: %.2f\n", a.name, a.balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("? Account not found!\n");
    }

    fclose(fp);
}

// ? Main Menu
int main() {
    int choice;

    do {
        printf("\n===== BANKING SYSTEM =====\n");
        printf("1. Create Account\n");
        printf("2. Display Accounts\n");
        printf("3. Deposit\n");
        printf("4. Withdraw\n");
        printf("5. Search Account\n");
        printf("6. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: displayAccounts(); break;
            case 3: deposit(); break;
            case 4: withdraw(); break;
            case 5: searchAccount(); break;
            case 6: printf("Thank you!\n"); break;
            default: printf("Invalid choice!\n");
        }

    } while(choice != 6);

    return 0;
}
