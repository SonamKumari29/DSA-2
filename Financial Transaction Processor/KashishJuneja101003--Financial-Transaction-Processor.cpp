#include <iostream>
#include <vector>
#include <iomanip> // For formatting output

using namespace std;

class FinancialTransactionProcessor {
public:
    enum class TransactionType { DEPOSIT, WITHDRAWAL, TRANSFER };

    struct Transaction {
        TransactionType type;
        double amount;
        int transactionHour;
        double transactionFee;

        Transaction(TransactionType t, double amt, int hour, double fee)
            : type(t), amount(amt), transactionHour(hour), transactionFee(fee) {}
    };

    FinancialTransactionProcessor(double initialBalance, const vector<Transaction>& trans)
        : balance(initialBalance), transactions(trans) {}

    pair<double, double> processTransactions() {
        double totalFee = 0;
        double currentBalance = balance;

        for (const auto& transaction : transactions) {
            if (isValidTransaction(transaction, currentBalance)) {
                double fee = calculateFee(transaction);
                updateBalance(transaction, currentBalance, fee);
                totalFee += fee;
            } else {
                cout << "Transaction failed due to insufficient balance or invalid input.\n";
            }
        }

        return {totalFee, currentBalance};
    }

private:
    double balance;
    vector<Transaction> transactions;

    bool isValidTransaction(const Transaction& transaction, double currentBalance) {
        if (transaction.amount <= 0) return false;

        switch (transaction.type) {
            case TransactionType::WITHDRAWAL:
            case TransactionType::TRANSFER:
                return (transaction.amount + transaction.transactionFee <= currentBalance);
            case TransactionType::DEPOSIT:
                return true;
            default:
                return false;
        }
    }

    double calculateFee(const Transaction& transaction) {
        if (transaction.type == TransactionType::DEPOSIT) {
            return 0; // No fee for deposits
        }
        return transaction.transactionFee; // Keep flexibility for future enhancements
    }

    void updateBalance(const Transaction& transaction, double& currentBalance, double fee) {
        switch (transaction.type) {
            case TransactionType::DEPOSIT:
                currentBalance += transaction.amount;
                break;
            case TransactionType::WITHDRAWAL:
            case TransactionType::TRANSFER:
                currentBalance -= (transaction.amount + fee);
                break;
        }
    }
};

int main() {
    double balance = 5000;

    vector<FinancialTransactionProcessor::Transaction> transactions = {
        {FinancialTransactionProcessor::TransactionType::DEPOSIT, 2000, 10, 0},
        {FinancialTransactionProcessor::TransactionType::WITHDRAWAL, 1500, 12, 3},
        {FinancialTransactionProcessor::TransactionType::TRANSFER, 1000, 15, 2},
        {FinancialTransactionProcessor::TransactionType::WITHDRAWAL, 6000, 18, 5} // Should fail
    };

    FinancialTransactionProcessor processor(balance, transactions);
    auto result = processor.processTransactions();

    cout << fixed << setprecision(2); // Formatting output for clarity
    cout << "\nFinal Report\n";
    cout << "-----------------------\n";
    cout << "Initial Balance: " << balance << "\n";
    cout << "Total Fees Charged: " << result.first << "\n";
    cout << "Final Balance: " << result.second << "\n";

    return 0;
}
