#include <iostream>
#include "login.h"
#include "input.h"
#include "customer.h"
#include "delivery.h"
#include "billing.h"
using namespace std;

CustomerManager cm;

void showMenu()
{
    cout << "\n=== Tiffin Tracker Pro ===\n";
    cout << "1. Add Customer\n";
    cout << "2. View Customers\n";
    cout << "3. Mark Tiffin Delivered\n";
    cout << "4. View Delivery Status\n";
    cout << "5. Generate Bill\n";
    cout << "6. View Deliveries by Date\n";
    cout << "7. Monthly Report\n";
    cout << "8. Export Customers to CSV\n";
    cout << "9. Import Customers from CSV\n";
    cout << "10. Export Deliveries to CSV\n";
    cout << "11. Import Deliveries from CSV\n";
    cout << "12. Edit Customer\n";
    cout << "13. Delete Customer\n";
    cout << "14. Edit Delivery\n";
    cout << "15. Delete Delivery\n";
    cout << "16. Exit\n";
}

int main()
{
    LoginManager lm;
    int loginChoice;

    do
    {
        cout << "\n1. Login\n2. Register\n3. Exit\nChoose: ";
        cin >> loginChoice;

        if (loginChoice == 1)
        {
            if (!lm.login()) continue;
            break;
        }
        else if (loginChoice == 2)
        {
            lm.registerUser();
        }
        else if (loginChoice == 3)
        {
            return 0;
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    } while (true);

    DeliveryManager dm;
    BillingManager bm;
    int choice;

    do
    {
        showMenu();
        choice = getIntInput("Enter your choice: ");

        switch (choice)
        {
        case 1: cm.addCustomer(); break;
        case 2: cm.viewCustomers(); break;
        case 3: dm.markDelivery(); break;
        case 4: dm.viewDeliveries(); break;
        case 5: bm.generateBill(); break;
        case 6: {
            string date;
            cout << "Enter date (YYYY-MM-DD): ";
            cin >> date;
            dm.viewDeliveriesByDate(date);
            break;
        }
        case 7: {
            string month;
            cout << "Enter month (YYYY-MM): ";
            cin >> month;
            dm.generateMonthlyReport(month);
            break;
        }
        case 8: cm.exportToCSV("customers_export.csv"); break;
        case 9: cm.importFromCSV("customers_import.csv"); break;
        case 10: dm.exportToCSV("deliveries_export.csv"); break;
        case 11: dm.importFromCSV("deliveries_import.csv"); break;
        case 12: {
            int id = getIntInput("Enter Customer ID to edit: ");
            cm.editCustomer(id);
            break;
        }
        case 13: {
            int id = getIntInput("Enter Customer ID to delete: ");
            cm.deleteCustomer(id);
            break;
        }
        case 14: {
            int id = getIntInput("Enter Customer ID: ");
            string date;
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;
            dm.editDelivery(id, date);
            break;
        }
        case 15: {
            int id = getIntInput("Enter Customer ID: ");
            string date;
            cout << "Enter Date (YYYY-MM-DD): ";
            cin >> date;
            dm.deleteDelivery(id, date);
            break;
        }
        case 16:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 16);

    return 0;
}
