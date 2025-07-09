#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct BankAccount {
    int accno;
    string name, address;
    char actype;
    float amount;

    BankAccount() : accno(0), name(""), address(""), actype('\0'), amount(0.0) {}
};

// Function to split a CSV line
vector<string> split(const string& s, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Load accounts from CSV file
void loadAccounts(vector<BankAccount>& accounts, const string& filename) {
    accounts.clear();
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<string> fields = split(line, ',');
        if (fields.size() == 5) {
            BankAccount acc;
            acc.accno = stoi(fields[0]);
            acc.name = fields[1];
            acc.address = fields[2];
            acc.actype = fields[3][0];
            acc.amount = stof(fields[4]);
            accounts.push_back(acc);
        }
    }
    file.close();
}

// Save accounts to CSV file
void saveAccounts(const vector<BankAccount>& accounts, const string& filename) {
    ofstream file(filename);
    for (const auto& acc : accounts) {
        file << acc.accno << "," << acc.name << "," << acc.address << "," << acc.actype << "," << acc.amount << endl;
    }
    file.close();
}

// Find account by number
int findAccount(const vector<BankAccount>& accounts, int accno) {
    for (size_t i = 0; i < accounts.size(); ++i) {
        if (accounts[i].accno == accno) return i;
    }
    return -1;
}

void createAccount(vector<BankAccount>& accounts) {
    BankAccount acc;
    cout << "Enter new account number: ";
    cin >> acc.accno;
    cin.ignore();
    cout << "Enter name: ";
    getline(cin, acc.name);
    cout << "Enter address: ";
    getline(cin, acc.address);
    cout << "Account type (s/c): ";
    cin >> acc.actype;
    cout << "Initial deposit: ";
    cin >> acc.amount;
    accounts.push_back(acc);
    cout << "Account created successfully.\n";
}

void deposit(vector<BankAccount>& accounts) {
    int accno;
    cout << "Enter account number: ";
    cin >> accno;
    int idx = findAccount(accounts, accno);
    if (idx == -1) {
        cout << "Account not found.\n";
        return;
    }
    float amt;
    cout << "Enter amount to deposit: ";
    cin >> amt;
    accounts[idx].amount += amt;
    cout << "Deposit successful. New balance: " << accounts[idx].amount << endl;
}

void withdraw(vector<BankAccount>& accounts) {
    int accno;
    cout << "Enter account number: ";
    cin >> accno;
    int idx = findAccount(accounts, accno);
    if (idx == -1) {
        cout << "Account not found.\n";
        return;
    }
    float amt;
    cout << "Enter amount to withdraw: ";
    cin >> amt;
    if (amt > accounts[idx].amount) {
        cout << "Insufficient funds.\n";
        return;
    }
    accounts[idx].amount -= amt;
    cout << "Withdrawal successful. New balance: " << accounts[idx].amount << endl;
}

void showAccount(const vector<BankAccount>& accounts) {
    int accno;
    cout << "Enter account number: ";
    cin >> accno;
    int idx = findAccount(accounts, accno);
    if (idx == -1) {
        cout << "Account not found.\n";
        return;
    }
    const BankAccount& acc = accounts[idx];
    cout << "Account No: " << acc.accno << "\nName: " << acc.name << "\nAddress: " << acc.address
         << "\nType: " << acc.actype << "\nBalance: " << acc.amount << endl;
}

void modifyAccount(vector<BankAccount>& accounts) {
    int accno;
    cout << "Enter account number: ";
    cin >> accno;
    int idx = findAccount(accounts, accno);
    if (idx == -1) {
        cout << "Account not found.\n";
        return;
    }
    cin.ignore();
    cout << "Enter new name: ";
    getline(cin, accounts[idx].name);
    cout << "Enter new address: ";
    getline(cin, accounts[idx].address);
    cout << "Enter new account type (s/c): ";
    cin >> accounts[idx].actype;
    cout << "Account modified successfully.\n";
}

void deleteAccount(vector<BankAccount>& accounts) {
    int accno;
    cout << "Enter account number: ";
    cin >> accno;
    int idx = findAccount(accounts, accno);
    if (idx == -1) {
        cout << "Account not found.\n";
        return;
    }
    accounts.erase(accounts.begin() + idx);
    cout << "Account deleted successfully.\n";
}

void showAllAccounts(const vector<BankAccount>& accounts) {
    if (accounts.empty()) {
        cout << "No accounts to display.\n";
        return;
    }
    for (const auto& acc : accounts) {
        cout << "Account No: " << acc.accno << ", Name: " << acc.name
             << ", Type: " << acc.actype << ", Balance: " << acc.amount << endl;
    }
}

int main() {
    vector<BankAccount> accounts;
    string filename = "accounts.csv";
    loadAccounts(accounts, filename);

    int choice;
    while (true) {
        cout << "\n--- Bank Management Menu ---\n";
        cout << "1. Create Account\n2. Deposit\n3. Withdraw\n4. Show Account\n5. Modify Account\n6. Delete Account\n7. Show All Accounts\n8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(accounts); break;
            case 2: deposit(accounts); break;
            case 3: withdraw(accounts); break;
            case 4: showAccount(accounts); break;
            case 5: modifyAccount(accounts); break;
            case 6: deleteAccount(accounts); break;
            case 7: showAllAccounts(accounts); break;
            case 8: saveAccounts(accounts, filename); cout << "Goodbye!\n"; return 0;
            default: cout << "Invalid choice.\n";
        }
        saveAccounts(accounts, filename);
    }
    return 0;
}
