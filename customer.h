#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Customer
{
    int id;
    string name;
    string phone;
    string address;
    string subscription;
};

class CustomerManager
{
    vector<Customer> customers;
    int nextId;

public:
    CustomerManager();
    void addCustomer();
    void viewCustomers();
    void saveToFile();
    void loadFromFile();
    void exportToCSV(const string& filename);
    void importFromCSV(const string& filename);
    void editCustomer(int id);
    void deleteCustomer(int id);
    string getSubscriptionType(int id);
};

#endif
