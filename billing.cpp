#define _CRT_SECURE_NO_WARNINGS  // optional alternative if using localtime()

#include "billing.h"
#include "customer.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>

extern CustomerManager cm;

void BillingManager::generateBill()
{
    int customerId, tiffinCount;
    float pricePerTiffin = 5.0;

    cout << "Enter Customer ID: ";
    cin >> customerId;
    cout << "Enter total tiffins delivered: ";
    cin >> tiffinCount;

    string subType = cm.getSubscriptionType(customerId);
    float total = tiffinCount * pricePerTiffin;

    time_t now = time(0);
    tm ltm;
    localtime_s(&ltm, &now); // safe alternative to localtime()

    char dateStr[20];
    strftime(dateStr, sizeof(dateStr), "%Y-%m-%d", &ltm);

    cout << "\n========== TIFFIN BILL RECEIPT ==========\n";
    cout << "Date: " << dateStr << "\n";
    cout << "Customer ID: " << customerId << "\n";
    cout << "Subscription: " << subType << "\n";
    cout << "Tiffins Delivered: " << tiffinCount << "\n";
    cout << fixed << setprecision(2);
    cout << "Rate per Tiffin: $" << pricePerTiffin << "\n";
    cout << "-------------------------------\n";
    cout << "Total Amount: $" << total << "\n";
    cout << "=========================================\n";

    ofstream out("receipt.txt", ios::app);
    out << "Date: " << dateStr << ", CustomerID: " << customerId
        << ", Tiffins: " << tiffinCount << ", Total: $" << total << "\n";
}
