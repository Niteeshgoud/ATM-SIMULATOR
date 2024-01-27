#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define a structure to represent an account
struct Account {
    char username[50];
    char pin[5];
    double balance;
};

// Function to create a new account
struct Account createAccount() {
    struct Account newAccount;

    printf("Enter your username: ");
    scanf("%s", newAccount.username);

    // Validate PIN input
    do {
        printf("Set your 4-digit PIN: ");
        scanf("%s", newAccount.pin);

        if (strlen(newAccount.pin) != 4) {
            printf("Invalid PIN. Please enter a 4-digit PIN.\n");
        }
    } while (strlen(newAccount.pin) != 4);

    newAccount.balance = 0.0;

    printf("Account created successfully!\n");

    return newAccount;
}

// Function to display account balance
void displayBalance(struct Account *account) {
    printf("Account balance for %s: $%.2f\n", account->username, account->balance);
}

// Function to deposit money
void deposit(struct Account *account, double amount) {
    account->balance += amount;
    printf("Deposit successful! New balance: $%.2f\n", account->balance);
}

// Function to withdraw money
bool withdraw(struct Account *account, double amount) {
    if (amount <= account->balance) {
        account->balance -= amount;
        printf("Withdrawal successful! New balance: $%.2f\n", account->balance);
        return true;  // Withdrawal successful
    } else {
        printf("Insufficient funds! Current balance: $%.2f\n", account->balance);
        return false;  // Withdrawal unsuccessful
    }
}

// Main function
int main() {
    struct Account userAccount;
    int choice;
    bool accountCreated = false;
    char continueChoice;

    while (1) {
        if (!accountCreated) {
            printf("Account not created. Would you like to create one? (y/n): ");
            scanf(" %c", &continueChoice);

            if (continueChoice == 'y' || continueChoice == 'Y') {
                userAccount = createAccount();
                accountCreated = true;
            } else {
                printf("Exiting ATM. Thank you!\n");
                exit(0);
            }
        } else {
            printf("Welcome to the ATM Simulator\n");
            printf("1. Display balance\n");
            printf("2. Deposit money\n");
            printf("3. Withdraw money\n");
            printf("4. Exit\n");

            printf("Enter your choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    displayBalance(&userAccount);
                    break;
                case 2:
                    printf("Enter the amount to deposit: $");
                    double depositAmount;
                    scanf("%lf", &depositAmount);
                    deposit(&userAccount, depositAmount);
                    break;
                case 3:
                    printf("Enter the amount to withdraw: $");
                    double withdrawAmount;
                    scanf("%lf", &withdrawAmount);

                    if (withdraw(&userAccount, withdrawAmount)) {
                        // Ask if the user wants to continue
                        printf("Do you want to continue? (y/n): ");
                        scanf(" %c", &continueChoice);
                    } else {
                        continueChoice = 'y';  // Retry withdrawal
                    }
                    break;
                case 4:
                    printf("Exiting ATM. Thank you!\n");
                    exit(0);
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }

        if (continueChoice != 'y' && continueChoice != 'Y') {
            break;  // Exit the loop if the user does not want to continue
        }
    }

    return 0;
}
