#include <iostream>
#include <string>
#include <stdexcept>
#include <Windows.h>

using namespace std;

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    BankAccount(int accNum, double initialBalance) {
        this->accountNumber = accNum;
        if (initialBalance < 0) {
            throw invalid_argument("Начальный баланс не может быть отрицательным.");
        }
        this->balance = initialBalance;
        this->interestRate = 0;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма внесения.");
        }
        balance += amount;
        cout << "Средства успешно внесены. Остаток на счете: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            throw invalid_argument("Некорректная сумма снятия.");
        }
        if (balance < amount) {
            throw invalid_argument("Недостаточно средств для снятия.");
        }
        balance -= amount;
        cout << "Средства успешно сняты. Остаток на счете: " << balance << endl;
    }

    double getBalance() {
        return balance;
    }

    double GetInterest() {
        return balance * interestRate * (1.0 / 12.0);
    }

    void setInterestRate(double rate) {
        interestRate = rate;
    }

    double getInterestRate() {
        return interestRate;
    }

    int getAccountNumber() {
        return accountNumber;
    }
};

bool transfer(BankAccount& from, BankAccount& to, double amount) {
    if (amount <= 0) {
        throw invalid_argument("Некорректная сумма перевода.");
    }
    if (from.getBalance() >= amount) {
        from.withdraw(amount);
        to.deposit(amount);
        cout << "Перевод успешно выполнен." << endl;
        return true;
    }
    else {
        throw invalid_argument("Недостаточно средств для совершения перевода.");
    }
}

int main() {
    SetConsoleCP(65001);
    setlocale(LC_ALL, "Russian");
    try {
        BankAccount acc1(20000, 1000);
        BankAccount acc2(10000, 500);

        int choice;
        double amount;
        bool success;

        while (true) {
            cout << "Выберите необходимую функцию:\n"
                "1. Пополнить счет\n"
                "2. Снять со счета\n"
                "3. Изменить % ставку\n"
                "4. Узнать текущую ставку\n"
                "5. Перевести\n"
                "6. Выйти\n";

            cout << " ";
            cin >> choice;

            if (choice == 1) {
                cout << "Введите сумму: ";
                cin >> amount;
                acc1.deposit(amount);
                
            }
            else if (choice == 2) {
                cout << "Введите сумму: ";
                cin >> amount;
                acc1.withdraw(amount);
              
            }
            else if (choice == 3) {
                cout << "Введите новую %  ставку: ";
                cin >> amount;
                acc1.setInterestRate(amount);
               
            }
            else if (choice == 4) {
                cout << "Текущая % ставка: " << acc1.getInterestRate() << "%\n";
                
            }
            else if (choice == 5) {
                cout << "Введите сумму: ";
                cin >> amount;
                success = transfer(acc1, acc2, amount);
                if (success) {
                    cout << "Баланс 1: " << acc1.getBalance() << "\n";
                    cout << "Баланс 2: " << acc2.getBalance() << "\n";
                }
               
            }
            else if (choice == 6) {
                return 0;
            }
            else {
                cout << "Выберите один из предложенных вариантов.\n";
            }
        }
    }
    catch (const invalid_argument& e) {
        cerr << "Ошибка: " << e.what() << "\n";
    }
    return 0;
}
