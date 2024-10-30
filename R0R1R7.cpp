#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Structure to represent user information
struct User {
    string userID;
    char accountType;  // 'T' (Trial), 'F' (Full), 'S' (Student)
    int tokenBalance;
    char autoTopUp;    // 'Y' or 'N'
};

// Structure for Student Data
struct StudentData {
    string studentName;
    string group;
};

// Global variables
vector<User> users;
vector<StudentData> studentDataList;
bool dataLoaded = false;

// Function declarations
void showMainMenu();
void loadStartingData();
void loadStudentData();
void exitProgram();
void selectAIService(User& user);

// Main function
int main() {
    int option = 0;

    // R0: Welcome message
    cout << "Welcome to the AI Service Token Management System!" << endl;

    // Load student data at the start
    loadStudentData();

    while (true) {
        showMainMenu();
        cin >> option;

        if (!dataLoaded && (option >= 2 && option <= 5)) {
            cout << "Error: You must load the starting data first (Option 1).\n" << endl;
            continue;
        }

        switch (option) {
        case 1: loadStartingData(); break;
        case 6: exitProgram(); break;  // Call exit function, do not exit directly
        default: cout << "Invalid option, please try again." << endl; break;
        }
    }
    return 0;
}

// Display the main menu
void showMainMenu() {
    const int width = 35;  // Total width of the menu box

    // Top border
    cout << string(width, '=') << endl;

    // Centered title
    string title = "Main Menu";
    int padding = (width - title.length() - 2) / 2;
    cout << "|" << string(padding, ' ') << title << string(width - padding - title.length() - 2, ' ') << "|" << endl;

    // Divider line
    cout << string(width, '=') << endl;

    // Menu options
    cout << "| " << setw(width - 3) << left << "[1] Load Starting Data" << "|" << endl;
    cout << "| " << setw(width - 3) << left << "[2] Show User Records" << "|" << endl;
    cout << "| " << setw(width - 3) << left << "[3] Edit Users" << "|" << endl;
    cout << "| " << setw(width - 3) << left << "[4] Enter User View" << "|" << endl;
    cout << "| " << setw(width - 3) << left << "[5] Show System Usage Summary" << "|" << endl;
    cout << "| " << setw(width - 3) << left << "[6] Credits and Exit" << "|" << endl;

    // Bottom border
    cout << string(width, '=') << endl;

    // Input prompt
    cout << "  Option (1 - 6): ";
}

// R1: Load starting data
void loadStartingData() {
    users = {
        {"SkyWalker", 'T', 20, 'N'},
        {"Ocean123", 'T', 35, 'N'},
        {"Forest99", 'T', 6, 'Y'},
        {"Valley777", 'F', 10, 'Y'},
        {"Desert2022", 'F', 25, 'N'},
        {"River456", 'F', 20, 'Y'},
        {"Blaze2023", 'F', 100, 'N'},
        {"Meadow888", 'S', 40, 'Y'},
        {"Galaxy", 'S', 15, 'Y'},
        {"Storm2024", 'S', 30, 'N'}
    };
    dataLoaded = true;
    cout << "Starting data loaded successfully!" << endl;
}

// Function to load student data (similar to R1 data loading)
void loadStudentData() {
    studentDataList = {
        {"\nXU Zhipeng 23062582S\nCHAN Tai Man 24*******\nCHAN Tai Man 24*******\nCHAN Tai Man 24*******\nCHAN Tai Man 24*******\nCHAN Tai Man 24*******", "101"}
    };
}

// R7: AI services
void selectAIService(User& user) {
    int aiCost = 0;
    int serviceChoice = 0;

    cout << "Select AI Service:" << endl;
    cout << "[1] Image Recognition" << endl;
    cout << "[2] Speech-to-Text Transcription" << endl;
    cout << "[3] Predictive Analysis" << endl;
    cout << "[4] Natural Language Processing (NLP)" << endl;
    cout << "Enter your choice (1-4): ";
    cin >> serviceChoice;

    switch (serviceChoice) {
    case 1: {  // Image Recognition
        float imageSize;
        cout << "Enter the image size in MB: ";
        cin >> imageSize;

        if (imageSize < 3) {
            aiCost = (user.accountType == 'S') ? 4 : 5;
        }
        else {
            if (user.accountType == 'F') {
                aiCost = 8;
            }
            else if (user.accountType == 'S') {
                aiCost = 7;
            }
            else {
                cout << "AI service denied. Trial accounts cannot use Image Recognition for images over 3 MB." << endl;
                return;
            }
        }
        break;
    }
    case 2: {  // Speech-to-Text Transcription
        int minutes;
        cout << "Enter the length of the audio file in minutes: ";
        cin >> minutes;
        aiCost = (minutes <= 3) ? (2 * minutes) : (2 * 3 + 3 * (minutes - 3));
        break;
    }
    case 3: {  // Predictive Analysis
        int tasks;
        cout << "Enter the number of prediction tasks: ";
        cin >> tasks;
        aiCost = 10 * tasks;
        break;
    }
    case 4: {  // Natural Language Processing
        int numCharacters;
        cout << "Enter the number of characters in the text: ";
        cin >> numCharacters;
        if (user.accountType == 'T' && numCharacters > 2500) {
            cout << "AI service denied. Trial accounts cannot process texts longer than 2500 characters." << endl;
            return;
        }
        aiCost = (numCharacters + 499) / 500;
        break;
    }
    default:
        cout << "Invalid service selection." << endl;
        return;
    }

    cout << "AI Service costs " << aiCost << " tokens." << endl;
}

// Exit program function
void exitProgram() {
    char confirm;
    cout << "Are you sure you want to exit? (y/n): ";
    cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        for (const auto& student : studentDataList) {
            cout << "\nStudent Name: " << student.studentName << endl;
            cout << "Group: " << student.group << endl;
            cout << "------------------------" << endl;
        }
        cout << "Exiting program. Thank you!" << endl;
        exit(0);
    }
    else {
        cout << "Exit canceled. Returning to Main Menu.\n" << endl;
    }
}
