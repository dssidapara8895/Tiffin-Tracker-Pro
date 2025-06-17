#include "delivery.h"
#include <fstream>

DeliveryManager::DeliveryManager()
{
    loadFromFile();
}

void DeliveryManager::markDelivery()
{
    Delivery d;
    cout << "Enter Customer ID: ";
    cin >> d.customerId;
    cout << "Enter Date (YYYY-MM-DD): ";
    cin.ignore();
    getline(cin, d.date);
    char status;
    cout << "Delivered? (y/n): ";
    cin >> status;
    d.delivered = (status == 'y' || status == 'Y');
    deliveries.push_back(d);
    saveToFile();
    cout << "Delivery record added.\n";
}

void DeliveryManager::viewDeliveries()
{
    if (deliveries.empty())
    {
        cout << "No delivery records found.\n";
        return;
    }
    for (const auto& d : deliveries)
    {
        cout << "Customer ID: " << d.customerId << ", Date: " << d.date
            << ", Status: " << (d.delivered ? "Delivered" : "Missed") << "\n";
    }
}

void DeliveryManager::viewDeliveriesByDate(const string& date)
{
    bool found = false;
    cout << "\n--- Deliveries on " << date << " ---\n";
    for (const auto& d : deliveries)
    {
        if (d.date == date)
        {
            cout << "Customer ID: " << d.customerId
                << ", Status: " << (d.delivered ? "Delivered" : "Missed") << "\n";
            found = true;
        }
    }
    if (!found)
        cout << "No deliveries found for this date.\n";
}

void DeliveryManager::generateMonthlyReport(const string& month)
{
    int total = 0, deliveredCount = 0, missed = 0;
    cout << "\n--- Monthly Report: " << month << " ---\n";
    for (const auto& d : deliveries)
    {
        if (d.date.substr(0, 7) == month)
        {
            cout << "Customer ID: " << d.customerId
                << ", Date: " << d.date
                << ", Status: " << (d.delivered ? "Delivered" : "Missed") << "\n";
            total++;
            d.delivered ? deliveredCount++ : missed++;
        }
    }
    if (total == 0)
        cout << "No deliveries found for this month.\n";
    else
    {
        cout << "\nSummary:\n";
        cout << "Total Deliveries: " << total << "\n";
        cout << "Delivered: " << deliveredCount << "\n";
        cout << "Missed: " << missed << "\n";
    }
}

void DeliveryManager::saveToFile()
{
    ofstream out("deliveries.txt");
    for (const auto& d : deliveries)
    {
        out << d.customerId << "," << d.date << "," << d.delivered << "\n";
    }
}

void DeliveryManager::loadFromFile()
{
    ifstream in("deliveries.txt");
    string line;
    while (getline(in, line))
    {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        Delivery d;
        d.customerId = stoi(line.substr(0, pos1));
        d.date = line.substr(pos1 + 1, pos2 - pos1 - 1);
        d.delivered = stoi(line.substr(pos2 + 1));
        deliveries.push_back(d);
    }
}

void DeliveryManager::exportToCSV(const string& filename)
{
    ofstream out(filename);
    out << "CustomerID,Date,Delivered\n";
    for (const auto& d : deliveries)
    {
        out << d.customerId << "," << d.date << "," << (d.delivered ? "Yes" : "No") << "\n";
    }
    cout << "Delivery data exported to " << filename << "\n";
}

void DeliveryManager::importFromCSV(const string& filename)
{
    ifstream in(filename);
    string line;
    getline(in, line); // skip header
    while (getline(in, line))
    {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        Delivery d;
        d.customerId = stoi(line.substr(0, pos1));
        d.date = line.substr(pos1 + 1, pos2 - pos1 - 1);
        string status = line.substr(pos2 + 1);
        d.delivered = (status == "Yes" || status == "yes");
        deliveries.push_back(d);
    }
    saveToFile();
    cout << "Delivery data imported from " << filename << "\n";
}

void DeliveryManager::editDelivery(int cid, const string& date)
{
    for (auto& d : deliveries)
    {
        if (d.customerId == cid && d.date == date)
        {
            cout << "Editing delivery for Customer ID " << cid << " on " << date << "\n";
            char status;
            cout << "Enter new status (y = Delivered, n = Missed): ";
            cin >> status;
            d.delivered = (status == 'y' || status == 'Y');
            saveToFile();
            cout << "Delivery updated.\n";
            return;
        }
    }
    cout << "Delivery not found.\n";
}

void DeliveryManager::deleteDelivery(int cid, const string& date)
{
    for (size_t i = 0; i < deliveries.size(); ++i)
    {
        if (deliveries[i].customerId == cid && deliveries[i].date == date)
        {
            deliveries.erase(deliveries.begin() + i);
            saveToFile();
            cout << "Delivery deleted.\n";
            return;
        }
    }
    cout << "Delivery not found.\n";
}
