#ifndef DELIVERY_H
#define DELIVERY_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Delivery
{
    int customerId;
    string date;
    bool delivered;
};

class DeliveryManager
{
    vector<Delivery> deliveries;

public:
    DeliveryManager();
    void markDelivery();
    void viewDeliveries();
    void viewDeliveriesByDate(const string& date);
    void generateMonthlyReport(const string& month);
    void saveToFile();
    void loadFromFile();
    void exportToCSV(const string& filename);
    void importFromCSV(const string& filename);
    void editDelivery(int customerId, const string& date);
    void deleteDelivery(int customerId, const string& date);
};

#endif
