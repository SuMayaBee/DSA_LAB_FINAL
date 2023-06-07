#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 100

// Structure to represent a bank account
typedef struct {
    char name[100];
    int accountNumber;
    char type[20];
    float totalBalance;
    float interestRate;
    char encryptedPassword[20];
    float transactionHistory[MAX_TRANSACTIONS];
    int transactionCount;
} Account;

// Array to store all accounts
Account accounts[MAX_ACCOUNTS];
// Variable to store the total number of accounts
int totalAccounts = 0;

// Function to generate a unique account number
int generateAccountNumber() {
    // Generate a random number or use a specific algorithm to ensure uniqueness
    // Example: return totalAccounts + 1;
}

// Function to add a new account
bool addAccount(char name[], char type[], float initialBalance, char password[]) {
    // Generate a unique account number
    int accountNumber = generateAccountNumber();

    // Check if the account number already exists
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return false;
        }
    }

    // If it doesn't exist, add the new account
    Account newAccount;
    strcpy(newAccount.name, name);
    newAccount.accountNumber = accountNumber;
    strcpy(newAccount.type, type);
    newAccount.totalBalance = initialBalance;
    encryptPassword(password, newAccount.encryptedPassword);
    newAccount.transactionCount = 0;

    accounts[totalAccounts++] = newAccount;

    return true;
}

// Function to display all accounts
void displayAccounts() {
    printf("Account Details:\n");
    for (int i = 0; i < totalAccounts; i++) {
        printf("Account %d\n", i + 1);
        printf("Name: %s\n", accounts[i].name);
        printf("Account number: %d\n", accounts[i].accountNumber);
        printf("Type: %s\n", accounts[i].type);
        printf("Total balance: %.2f\n", accounts[i].totalBalance);
        printf("\n");
    }
}

// Function to search for an account by account number
Account* searchAccount(int accountNumber) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return &accounts[i];
        }
    }
    return NULL;
}

// Function to delete an account by account number
bool deleteAccount(int accountNumber) {
    for (int i = 0; i < totalAccounts; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            // Shift elements to remove the account
            for (int j = i; j < totalAccounts - 1; j++) {
                accounts[j] = accounts[j + 1];
            }
            totalAccounts--;
            return true;
        }
    }
    return false;
}

// Function to sort accounts based on total balance
void sortAccountsByBalance() {
    for (int i = 0; i < totalAccounts - 1; i++) {
        for (int j = 0; j < totalAccounts - i - 1; j++) {
            if (accounts[j].totalBalance > accounts[j + 1].totalBalance) {
                Account temp = accounts[j];
                accounts[j] = accounts[j + 1];
                accounts[j + 1] = temp;
            }
        }
    }
    printf("Accounts sorted by balance.\n");
}

// Function to deposit amount into an account
bool deposit(int accountNumber, float amount) {
    Account* account = searchAccount(accountNumber);
    if (account != NULL) {
        account->totalBalance += amount;
        // Update transaction history
        account->transactionHistory[account->transactionCount++] = amount;
        return true;
    }
    return false;
}

// Function to withdraw amount from an account
bool withdraw(int accountNumber, float amount) {
    Account* account = searchAccount(accountNumber);
    if (account != NULL) {
        if (account->totalBalance >= amount) {
            account->totalBalance -= amount;
            // Update transaction history
            account->transactionHistory[account->transactionCount++] = -amount;
            return true;
        } else {
            printf("Insufficient balance in the account.\n");
        }
    }
    return false;
}

// Function to update account details
bool updateAccount(int accountNumber, char name[], char type[], char password[]) {
    Account* account = searchAccount(accountNumber);
    if (account != NULL) {
        strcpy(account->name, name);
        strcpy(account->type, type);
        encryptPassword(password, account->encryptedPassword);
        return true;
    }
    return false;
}

// Function to check the account password
bool checkPassword(int accountNumber, char password[]) {
    Account* account = searchAccount(accountNumber);
    if (account != NULL) {
        char decryptedPassword[20];
        decryptPassword(account->encryptedPassword, decryptedPassword);
        if (strcmp(decryptedPassword, password) == 0) {
            return true;
        }
    }
    return false;
}

// Function to encrypt the password
void encryptPassword(const char* password, char* encryptedPassword) {
    int i = 0;
    char c;
    while ((c = password[i]) != '\0') {
        if (c >= 'a' && c <= 'z') {
            encryptedPassword[i] = 'a' + (c - 'a' + 3) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            encryptedPassword[i] = 'A' + (c - 'A' + 3) % 26;
        } else {
            encryptedPassword[i] = c;
        }
        i++;
    }
    encryptedPassword[i] = '\0';
}

// Function to decrypt the password
void decryptPassword(const char* encryptedPassword, char* decryptedPassword) {
    int i = 0;
    char c;
    while ((c = encryptedPassword[i]) != '\0') {
        if (c >= 'a' && c <= 'z') {
            decryptedPassword[i] = 'a' + (c - 'a' - 3 + 26) % 26;
        } else if (c >= 'A' && c <= 'Z') {
            decryptedPassword[i] = 'A' + (c - 'A' - 3 + 26) % 26;
        } else {
            decryptedPassword[i] = c;
        }
        i++;
    }
    decryptedPassword[i] = '\0';
}

// Function to display transaction history for an account
void displayTransactionHistory(int accountNumber) {
    Account* account = searchAccount(accountNumber);
    if (account != NULL) {
        printf("Transaction History for Account %d:\n", accountNumber);
        for (int i = 0; i < account->transactionCount; i++) {
            if (account->transactionHistory[i] >= 0) {
                printf("Deposit: %.2f\n", account->transactionHistory[i]);
            } else {
                printf("Withdrawal: %.2f\n", -account->transactionHistory[i]);
            }
        }
    } else {
        printf("Account not found.\n");
    }
}

// Function to handle errors and display error messages
void handleError(const char* message) {
    printf("Error: %s\n", message);
}

int main() {
    char name[100];
    char type[20];
    float initialBalance;
    char password[20];

    while (1) {
        printf("Enter the following details to add a new account:\n");
        printf("Name: ");
        scanf("%s", name);
        printf("Type (current/saving/fixed deposit): ");
        scanf("%s", type);
        printf("Initial balance: ");
        scanf("%f", &initialBalance);
        printf("Password: ");
        scanf("%s", password);

        addAccount(name, type, initialBalance, password);
        printf("Account added successfully!\n");

        printf("Do you want to continue (1 for yes, 0 for no): ");
        int choice;
        scanf("%d", &choice);

        if (choice == 0) {
            break;
        }
    }

    displayAccounts();

    // Example usage of other functions
    int accountNumberToDelete = 1;
    if (deleteAccount(accountNumberToDelete)) {
        printf("Account with account number %d deleted successfully.\n", accountNumberToDelete);
    } else {
        handleError("Failed to delete account. Account number not found.");
    }

    int accountNumberToSearch = 2;
    Account* foundAccount = searchAccount(accountNumberToSearch);
    if (foundAccount != NULL) {
        printf("Account found:\n");
        printf("Name: %s\n", foundAccount->name);
        printf("Account number: %d\n", foundAccount->accountNumber);
        printf("Type: %s\n", foundAccount->type);
        printf("Total balance: %.2f\n", foundAccount->totalBalance);
    } else {
        handleError("Account not found.");
    }

    sortAccountsByBalance();

    int accountNumberToDeposit = 2;
    float amountToDeposit = 500.0;
    if (deposit(accountNumberToDeposit, amountToDeposit)) {
        printf("Deposit of %.2f successfully made to account %d.\n", amountToDeposit, accountNumberToDeposit);
    } else {
        handleError("Failed to deposit. Account not found.");
    }

    int accountNumberToWithdraw = 2;
    float amountToWithdraw = 200.0;
    if (withdraw(accountNumberToWithdraw, amountToWithdraw)) {
        printf("Withdrawal of %.2f successfully made from account %d.\n", amountToWithdraw, accountNumberToWithdraw);
    } else {
        handleError("Failed to withdraw. Account not found or insufficient balance.");
    }

    int accountNumberToUpdate = 2;
    char newName[100] = "Updated Name";
    char newType[20] = "Updated";
    char newPassword[20] = "newpassword";
    if (updateAccount(accountNumberToUpdate, newName, newType, newPassword)) {
        printf("Account details updated successfully.\n");
    } else {
        handleError("Failed to update account details. Account not found.");
    }

    displayTransactionHistory(2);

    return 0;
}



/*
Input:

Enter the following details to add a new account:
Name: John Doe
Type (current/saving/fixed deposit): saving
Initial balance: 5000.00
Password: mypassword
Do you want to continue (1 for yes, 0 for no): 1

Enter the following details to add a new account:
Name: Jane Smith
Type (current/saving/fixed deposit): current
Initial balance: 10000.00
Password: password123
Do you want to continue (1 for yes, 0 for no): 0

Output:

Account added successfully!
Account added successfully!

Account Details:
Account 1
Name: John Doe
Account number: 1
Type: saving
Total balance: 5000.00

Account 2
Name: Jane Smith
Account number: 2
Type: current
Total balance: 10000.00

Account with account number 1 deleted successfully.
Account found:
Name: Jane Smith
Account number: 2
Type: current
Total balance: 10000.00

Accounts sorted by balance.

Deposit of 500.00 successfully made to account 2.
Withdrawal of 200.00 successfully made from account 2.

Account details updated successfully.

Transaction History for Account 2:
Deposit: 500.00
Withdrawal: 200.00

*/