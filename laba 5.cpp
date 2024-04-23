#include <fstream>
#include <string>
#include <list>
#include <deque>
#include <set>
#include <unordered_set>
#include <algorithm>

using namespace std;

class BankCredit {
private:
    string name;
    double amount;
    string currency;
    double interestRate;

public:
    BankCredit(const string& name, double amount, const string& currency, double interestRate)
        : name(name), amount(amount), currency(currency), interestRate(interestRate) {}

    friend ostream& operator<<(ostream& os, const BankCredit& credit) {
        os << "Name: " << credit.name << ", Amount: " << credit.amount << " " << credit.currency
            << ", Interest Rate: " << credit.interestRate << "%";
        return os;
    }

    bool operator<(const BankCredit& other) const {
        return amount < other.amount;
    }

    bool operator==(const BankCredit& other) const {
        return amount == other.amount;
    }

    double getAmount() const {
        return amount;
    }

};

struct BankCreditHash {
    size_t operator()(const BankCredit& credit) const {
        return std::hash<double>()(credit.getAmount());
    }
};

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output.txt");

    deque<BankCredit> creditsDeque;

    string name, currency;
    double amount, interestRate;

    while (inputFile >> name >> amount >> currency >> interestRate) {
        BankCredit credit(name, amount, currency, interestRate);
        creditsDeque.push_back(credit);
    }
    outputFile << "Original Deque:" << endl;
    for (const BankCredit& credit : creditsDeque) {
        outputFile << credit << endl;
    }

    // Add objects to set
    set<BankCredit> creditsSet(creditsDeque.begin(), creditsDeque.end());

    outputFile << "\nSet:" << endl;
    for (const BankCredit& credit : creditsSet) {
        outputFile << credit << endl;
    }

    // Add objects to unordered_set
    unordered_set<BankCredit, BankCreditHash> creditsUnorderedSet(creditsDeque.begin(), creditsDeque.end());

    outputFile << "\nUnordered Set:" << endl;
    for (const BankCredit& credit : creditsUnorderedSet) {
        outputFile << credit << endl;
    }

    inputFile.close();
    outputFile.close();

    return 0;
}