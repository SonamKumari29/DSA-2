#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class FinancialTransactionProcessor {
public:
    // Enum class for transaction types
    enum class TransactionType { DEPOSIT, WITHDRAWAL, TRANSFER };

    // Transaction struct to hold transaction data
    struct Transaction {
        TransactionType type;  // Transaction type
        double amount;         // Amount of transaction
        int transactionHour;   // Hour of transaction
        double transactionFee; // Fee for the transaction

        // Constructor for easy initialization
        Transaction(TransactionType t, double amt, int hour, double fee)
            : type(t), amount(amt), transactionHour(hour), transactionFee(fee) {}
    };

    FinancialTransactionProcessor(double balance, const vector<Transaction>& transactions)
        : balance(balance), transactions(transactions) {}

    // Method to process transactions and calculate fees and final balance
    pair<double, double> processTransactions() {
        double totalFee = 0;
        double currentBalance = balance;

        for (const auto& transaction : transactions) {
            if (isValidTransaction(transaction, currentBalance)) {
                updateBalance(transaction, currentBalance, totalFee);
            }
        }

        return {totalFee, currentBalance}; // Return total fee and final balance
    }

private:
    double balance;
    vector<Transaction> transactions;

    // Method to validate transactions
    bool isValidTransaction(const Transaction& transaction, double currentBalance) {
        switch (transaction.type) {
            case TransactionType::WITHDRAWAL:
            case TransactionType::TRANSFER:
                return transaction.amount + transaction.transactionFee <= currentBalance;
            case TransactionType::DEPOSIT:
                return transaction.amount > 0; // Deposits are always valid if amount is positive
            default:
                return false;
        }
    }

    // Method to update balance based on transaction type
    void updateBalance(const Transaction& transaction, double& currentBalance, double& totalFee) {
        switch (transaction.type) {
            case TransactionType::DEPOSIT:
                currentBalance += transaction.amount;
                break;
            case TransactionType::WITHDRAWAL:
            case TransactionType::TRANSFER:
                currentBalance -= transaction.amount;
                break;
        }
        currentBalance -= transaction.transactionFee; // Deduct fee
        totalFee += transaction.transactionFee;       // Accumulate total fees
    }
};

int main() {
    double balance = 5000;

    // Sample transactions
    vector<FinancialTransactionProcessor::Transaction> transactions = {
        {FinancialTransactionProcessor::TransactionType::DEPOSIT, 2000, 10, 5},
        {FinancialTransactionProcessor::TransactionType::WITHDRAWAL, 1500, 12, 3},
        {FinancialTransactionProcessor::TransactionType::TRANSFER, 1000, 15, 2}
    };

    // Create processor instance
    FinancialTransactionProcessor processor(balance, transactions);

    // Process the transactions
    auto result = processor.processTransactions();

    // Output the result
    cout << "Total Fee: " << result.first << endl;
    cout << "Final Balance: " << result.second << endl;

    return 0;
}
