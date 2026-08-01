#include <bits/stdc++.h>
#include <fstream>
#include <map>
#include <vector>
#include <string>
using namespace std;

// ====================== Utility Functions ======================

// Function to get a **safe integer input**
int getIntInput(const string &prompt, int minVal = INT_MIN, int maxVal = INT_MAX) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            if (value >= minVal && value <= maxVal) {
                // cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear buffer
                return value;
            } else {
                cout << "Please enter a valid number between " << minVal << " and " << maxVal << ".\n";
            }
        } else {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard bad input
        }
    }
}

// Function to get a **yes/no confirmation**
bool getYesNoInput(const string &prompt) {
    char ch='n';
    while (true) {
        cout << prompt;
        if (cin >> ch) {
            ch = tolower(ch);
            if (ch == 'y') return true;
            if (ch == 'n') return false;
            cout << "Please enter Y or N only.\n";
        } else {
            cout << "Invalid input! Please enter Y or N.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

// ====================== Classes ======================

class User {
    string username, password;

public:
    void registerUser() {
        cout << "Enter new username:";
        // cin.ignore();
        getline(cin, username);

        cout << "Enter new password:";
        getline(cin, password);

        ofstream file("users.txt", ios::app);
        file << username << " " << password << endl;
        file.close();

        cout << "Registration successful.\n";
    }

    bool loginUser() {
        string user, pass;
        cout << "Enter username: ";
        cin >> user;
        cout << "Enter password: ";
        cin >> pass;

        ifstream file("users.txt");
        string fileUser, filePass;
        while (file >> fileUser >> filePass) {
            if (user == fileUser && pass == filePass) {
                cout << "Login successful.\n";
                return true;
            }
        }
        cout << "Login failed.\n";
        return false;
    }
};

class TrafficControl {
public:
    void controlSignal() {
        struct DirectionData {
            string name;
            int vehicleCount;
            bool hasEmergency=false;
            int greenDuration;
        };

        string directions[4] = {"North", "East", "South", "West"};
        vector<DirectionData> data;

        for (int i = 0; i < 4; ++i) {
            DirectionData d;
            d.name = directions[i];
            d.vehicleCount = getIntInput("Enter number of vehicles in " + d.name + ": ", 0);
            if(d.vehicleCount)
            d.hasEmergency = getYesNoInput("Is there an emergency vehicle in " + d.name + "? (y/n): ");
            d.greenDuration = d.vehicleCount>0?(20 + d.vehicleCount):0;
            data.push_back(d);
        }

        sort(data.begin(), data.end(), [](const DirectionData &a, const DirectionData &b) {
            if (a.hasEmergency != b.hasEmergency)
                return a.hasEmergency > b.hasEmergency;
            return a.vehicleCount > b.vehicleCount;
        });

        ofstream log("signal_log.txt", ios::app);
        log << "=== Traffic Signal Sequence ===\n";

        cout << "\n Traffic Signal Green Light Order:\n";
        for (size_t i = 0; i < data.size(); ++i) {
            cout << i + 1 << ". " << data[i].name
                 << " | Vehicles: " << data[i].vehicleCount
                 << " | Emergency: " << (data[i].hasEmergency ? "Yes" : "No")
                 << " | Duration: " << data[i].greenDuration << " seconds\n";

            log << i + 1 << ". " << data[i].name
                << " | Vehicles: " << data[i].vehicleCount
                << " | Emergency: " << (data[i].hasEmergency ? "Yes" : "No")
                << " | Duration: " << data[i].greenDuration << " seconds\n";
        }
        log << "===============================\n\n";
        log.close();
    }
};

class Violation {
public:
    void reportViolation() {
        string vehicleNumber;
        vector<string> violationTypes = {
            "Over-speeding", "No Helmet", "Use of Mobile Phone",
            "Seat Belt Not Worn", "Disobeying Traffic Signal",
            "Wrong Lane Driving", "Driving Without License"
        };

        vector<int> penalties = {1000, 500, 800, 400, 1200, 700, 1500};

        cout << "Enter vehicle number: ";
        cin >> vehicleNumber;

        cout << "Select type of violation:\n";
        for (size_t i = 0; i < violationTypes.size(); ++i) {
            cout << i + 1 << ". " << violationTypes[i] << " (Penalty: Rs" << penalties[i] << ")\n";
        }

        int violationChoice = getIntInput("Choice: ", 1, violationTypes.size());
        string violation = violationTypes[violationChoice - 1];
        int penalty = penalties[violationChoice - 1];

        int challanId = 1000;
        ifstream idFile("challan_id.txt");
        if (idFile >> challanId) challanId++;
        idFile.close();

        ofstream idOut("challan_id.txt");
        idOut << challanId;
        idOut.close();

        ofstream file("violations.txt", ios::app);
        file << "Challan No: " << challanId
             << " | Vehicle: " << vehicleNumber
             << " | Violation: " << violation
             << " | Penalty: Rs" << penalty << "\n";
        file.close();

        cout << "Violation reported successfully.\n";
        cout << "Challan Number: " << challanId << " | Penalty: Rs" << penalty << endl;
    }

    void viewViolations() {
        ifstream file("violations.txt");
        string line;
        cout << "Reported Violations:\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
    }
};

class Emergency {
public:
    void reportEmergency() {
        vector<string> emergencyTypes = {
            "Men at Work", "Bridge Collapse", "Road Accident",
            "Water Logging", "Tree/Pole Falling"
        };

        string streetName;
        cout << "Enter street name: ";
        // cin.ignore();
        getline(cin, streetName);

        cout << "Select type of emergency:\n";
        for (size_t i = 0; i < emergencyTypes.size(); ++i) {
            cout << i + 1 << ". " << emergencyTypes[i] << endl;
        }

        int emergencyChoice = getIntInput("Choice: ", 1, emergencyTypes.size());
        string selectedEmergency = emergencyTypes[emergencyChoice - 1];

        ofstream file("emergencies.txt", ios::app);
        file << "Street: " << streetName
             << " | Emergency: " << selectedEmergency << "\n";
        file.close();

        cout << "Emergency reported successfully.\n";
        cout << "Street: " << streetName << " | Emergency: " << selectedEmergency << endl;
    }

    void viewEmergencies() {
        cout << "\nView Emergency Reports:\n";
        cout << "1. By Street Location\n";
        cout << "2. By Emergency Type\n";
        cout << "3. All\n";
        int choice = getIntInput("Choice: ", 1, 3);

        cin.ignore();
        string searchTerm;
        if (choice == 1) {
            cout << "Enter street name: ";
            getline(cin, searchTerm);
        } else if (choice == 2) {
            cout << "Enter emergency type (e.g., Road Accident): ";
            getline(cin, searchTerm);
        } else {
            ifstream file("emergencies.txt");
            string line;
            cout << "Reported Emergencies:\n";
            while (getline(file, line)) {
                cout << line << endl;
            }
            return;
        }

        ifstream file("emergencies.txt");
        string line;
        bool found = false;
        cout << "\nMatching Emergency Reports:\n";
        while (getline(file, line)) {
            if (line.find(searchTerm) != string::npos) {
                cout << line << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "No emergencies found matching: " << searchTerm << endl;
        }
    }
};

// ====================== Main ======================
int main() {
    User user;
    TrafficControl tc;
    Violation violation;
    Emergency emergency;

    while (true) {
        int choice = getIntInput("\n1. Register\n2. Login\n0. Exit\nChoice: ", 0, 2);
        if (choice == 1) {
            user.registerUser();
        } else if (choice == 2) {
            if (user.loginUser()) {
                while (true) {
                    cout << "\n1. Control Traffic Signal\n"
                         << "2. Report Violation\n"
                         << "3. View Violations\n"
                         << "4. Report Emergency\n"
                         << "5. View Emergencies\n"
                         << "0. Logout\n";

                    int option = getIntInput("Choice: ", 0, 5);
                    switch (option) {
                        case 1: tc.controlSignal(); break;
                        case 2: violation.reportViolation(); break;
                        case 3: violation.viewViolations(); break;
                        case 4: emergency.reportEmergency(); break;
                        case 5: emergency.viewEmergencies(); break;
                        case 0: goto logout;
                    }
                }
                logout:;
            }
        } else if (choice == 0) {
            cout << "Exiting program.\n";
            break;
        }
    }
    return 0;
}
