#define _CRT_SECURE_NO_WARNINGS  // ✅ Fixes getenv() warning

#include "customer.h"
#include <fstream>

CustomerManager::CustomerManager()
{
    nextId = 1;
    loadFromFile();
}

void CustomerManager::addCustomer()
{
    Customer c;
    c.id = nextId++;

    cin.ignore();  // 🛠️ Clear buffer before getline
    cout << "Enter name: ";
    getline(cin, c.name);

    cout << "Enter phone: ";
    getline(cin, c.phone);

    cout << "Enter address: ";
    getline(cin, c.address);

    cout << "Enter subscription type (Daily/Weekly/Monthly): ";
    getline(cin, c.subscription);

    customers.push_back(c);
    saveToFile();
    cout << "[OK] Customer added successfully!\n";
}

void CustomerManager::viewCustomers()
{
    if (customers.empty())
    {
        cout << "[INFO] No customers found.\n";
        return;
    }

    for (const auto& c : customers)
    {
        cout << "ID: " << c.id << ", Name: " << c.name
            << ", Phone: " << c.phone << ", Address: " << c.address
            << ", Subscription: " << c.subscription << "\n";
    }
}

void CustomerManager::saveToFile()
{
    ofstream out("customers.txt");
    for (const auto& c : customers)
    {
        out << c.id << "," << c.name << "," << c.phone << "," << c.address << "," << c.subscription << "\n";
    }
}

void CustomerManager::loadFromFile()
{
    ifstream in("customers.txt");
    string line;
    Customer c;

    while (getline(in, line))
    {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        c.id = stoi(line.substr(0, pos1));
        c.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        c.phone = line.substr(pos2 + 1, pos3 - pos2 - 1);
        c.address = line.substr(pos3 + 1, pos4 - pos3 - 1);
        c.subscription = line.substr(pos4 + 1);

        customers.push_back(c);
        if (c.id >= nextId) nextId = c.id + 1;
    }
}

void CustomerManager::exportToCSV(const string& filename)
{
    char* username = getenv("USERNAME");
    string path = "C:\\Users\\" + string(username) + "\\Desktop\\" + filename;

    ofstream out(path);
    out << "ID,Name,Phone,Address,Subscription\n";
    for (const auto& c : customers)
    {
        out << c.id << "," << c.name << "," << c.phone << "," << c.address << "," << c.subscription << "\n";
    }
    out.close();

    cout << "[OK] Customer data exported to Desktop: " << filename << "\n";
    system(("start " + path).c_str());
}

void CustomerManager::importFromCSV(const string& filename)
{
    char* username = getenv("USERNAME");
    string path = "C:\\Users\\" + string(username) + "\\Desktop\\" + filename;

    ifstream in(path);
    string line;
    getline(in, line); // skip header

    while (getline(in, line))
    {
        Customer c;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);

        c.id = stoi(line.substr(0, pos1));
        c.name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        c.phone = line.substr(pos2 + 1, pos3 - pos2 - 1);
        c.address = line.substr(pos3 + 1, pos4 - pos3 - 1);
        c.subscription = line.substr(pos4 + 1);

        customers.push_back(c);
        if (c.id >= nextId) nextId = c.id + 1;
    }

    saveToFile();
    cout << "[OK] Customer data imported from Desktop: " << filename << "\n";
}

void CustomerManager::editCustomer(int id)
{
    for (auto& c : customers)
    {
        if (c.id == id)
        {
            cout << "Editing customer ID: " << id << "\n";
            string input;

            cin.ignore();  // 🛠️ Make sure first input isn't skipped
            cout << "New Name (current: " << c.name << "): ";
            getline(cin, input);
            if (!input.empty()) c.name = input;

            cout << "New Phone (current: " << c.phone << "): ";
            getline(cin, input);
            if (!input.empty()) c.phone = input;

            cout << "New Address (current: " << c.address << "): ";
            getline(cin, input);
            if (!input.empty()) c.address = input;

            cout << "New Subscription (current: " << c.subscription << "): ";
            getline(cin, input);
            if (!input.empty()) c.subscription = input;

            saveToFile();
            cout << "[OK] Customer updated.\n";
            return;
        }
    }
    cout << "[ERROR] Customer ID not found.\n";
}

void CustomerManager::deleteCustomer(int id)
{
    for (size_t i = 0; i < customers.size(); ++i)
    {
        if (customers[i].id == id)
        {
            customers.erase(customers.begin() + i);
            saveToFile();
            cout << "[OK] Customer deleted.\n";
            return;
        }
    }
    cout << "[ERROR] Customer ID not found.\n";
}

string CustomerManager::getSubscriptionType(int id)
{
    for (const auto& c : customers)
    {
        if (c.id == id)
            return c.subscription;
    }
    return "Unknown";
}
