#include "login.h"

bool LoginManager::checkCredentials(const string& u, const string& p)
{
    ifstream file("users.txt");
    string fileUser, filePass;

    while (file >> fileUser >> filePass)
    {
        if (u == fileUser && p == filePass)
            return true;
    }
    return false;
}

bool LoginManager::login()
{
    string username, password;
    cout << "\n=== Login ===\n";
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (checkCredentials(username, password))
    {
        cout << "Login successful!\n";
        return true;
    }
    else
    {
        cout << "Login failed. Invalid username or password.\n";
        return false;
    }
}

void LoginManager::registerUser()
{
    string username, password;
    cout << "\n=== Register New User ===\n";
    cout << "Choose a username: ";
    cin >> username;
    cout << "Choose a password: ";
    cin >> password;

    if (checkCredentials(username, password))
    {
        cout << "User already exists!\n";
        return;
    }

    ofstream file("users.txt", ios::app);
    file << username << " " << password << "\n";
    file.close();

    cout << "User registered successfully!\n";
}
