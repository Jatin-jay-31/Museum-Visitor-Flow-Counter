#include <iostream>
#include <string>
#include <sstream>
using namespace std;

enum class MovementType { ENTRY, EXIT };
class VisitorRecord
{
private:
    int recordID;
    string visitorLabel;
    MovementType movementType;
    int visitorCount;
    string gateName;
    static int totalRecords;
public:
    VisitorRecord()
        : recordID(0), visitorLabel(""),
          movementType(MovementType::ENTRY), visitorCount(0), gateName("") {}

    void setDetails(int id, const string &label, MovementType type,
                    int count, const string &gate)
    {
        this->recordID = id;
        this->visitorLabel = label;
        this->movementType = type;
        this->visitorCount = count;
        this->gateName = gate;
        totalRecords++;
    }
    inline int getID() const { return recordID; }
    inline MovementType getType() const { return movementType; }
    inline int getVisitorCount() const { return visitorCount; }

    static void displayTotalRecords()
    {
        cout << "\nTotal movement records added: " << totalRecords << '\n';
    }
    friend void displayRecord(const VisitorRecord &record);
};
int VisitorRecord::totalRecords = 0;
void displayRecord(const VisitorRecord &record)
{
    cout << "\nRecord ID       : " << record.recordID;
    cout << "\nVisitor/Group   : " << record.visitorLabel;
    cout << "\nMovement Type   : "
         << (record.movementType == MovementType::ENTRY ? "ENTRY" : "EXIT");
    cout << "\nVisitor Count   : " << record.visitorCount;
    cout << "\nGate Name       : " << record.gateName << '\n';
}
int readInteger(const string &message)
{
    string input;
    int value;
    while (true)
    {
        cout << message;
        getline(cin, input);
        stringstream ss(input);
        char extra;
        if (ss >> value && !(ss >> extra))
            return value;
        cout << "Invalid input. Please enter a whole number.\n";
    }
}
string readNonEmptyString(const string &message)
{
    string value;
    while (true)
    {
        cout << message;
        getline(cin, value);
        if (value.find_first_not_of(" \t") != string::npos)
            return value;
        cout << "This field cannot be empty. Please try again.\n";
    }
}
bool isDuplicateID(int id, const VisitorRecord *records, int recordCount)
{
    for (int i = 0; i < recordCount; i++)
        if ((records + i)->getID() == id)
            return true;
    return false;
}
bool updateVisitorCount(int people, MovementType type, int *currentVisitors)
{
    if (type == MovementType::ENTRY)
        *currentVisitors += people;
    else
    {
        if (people > *currentVisitors)
        {
            cout << "\nExit rejected: only " << *currentVisitors
                 << " visitor(s) are currently inside.\n";
            return false;
        }
        *currentVisitors -= people;
    }
    return true;
}
void addRecord(VisitorRecord records[], int &recordCount, int &currentVisitors)
{
    const int MAX_RECORDS = 50;
    if (recordCount >= MAX_RECORDS)
    {
        cout << "\nRecord storage is full.\n";
        return;
    }
    cout << "\n========== ADD VISITOR MOVEMENT ==========\n";
    int id = readInteger("Enter record ID: ");
    if (id <= 0)
    {
        cout << "Record ID must be positive.\n";
        return;
    }
    if (isDuplicateID(id, records, recordCount))
    {
        cout << "Duplicate record ID. Record not added.\n";
        return;
    }
    string label = readNonEmptyString("Enter visitor/group label: ");
    cout << "\n1. ENTRY\n2. EXIT\n";
    int typeChoice = readInteger("Select movement type: ");
    MovementType type;
    if (typeChoice == 1)
        type = MovementType::ENTRY;
    else if (typeChoice == 2)
        type = MovementType::EXIT;
    else
    {
        cout << "Invalid movement type. Record not added.\n";
        return;
    }
    int people = readInteger("Enter number of visitors: ");
    if (people <= 0)
    {
        cout << "Visitor count must be greater than zero.\n";
        return;
    }
    string gate = readNonEmptyString("Enter gate/access point name: ");
    if (!updateVisitorCount(people, type, &currentVisitors))
        return;
    VisitorRecord *ptr = &records[recordCount];
    ptr->setDetails(id, label, type, people, gate);
    recordCount++;
    cout << "\nRecord added successfully.\n";
    cout << "Current visitors inside: " << currentVisitors << '\n';
}

void viewRecords(const VisitorRecord *records, int recordCount)
{
    cout << "\n========== ALL MOVEMENT RECORDS ==========\n";
    if (recordCount == 0)
    {
        cout << "No records have been added yet.\n";
        return;
    }
    for (int i = 0; i < recordCount; i++)
    {
        const VisitorRecord *ptr = records + i;
        cout << "\n---------- Record " << i + 1 << " ----------";
        displayRecord(*ptr);
    }
    VisitorRecord::displayTotalRecords();
}
void displayCurrentCount(int currentVisitors)
{
    cout << "\nCurrent visitors inside the museum: "
         << currentVisitors << '\n';
    VisitorRecord::displayTotalRecords();
}
int main()
{
    const int MAX_RECORDS = 50;
    VisitorRecord records[MAX_RECORDS];
    int recordCount = 0;
    int currentVisitors = 0;
    int choice;
    cout << "--------------------------------------------\n";
    cout << "       MUSEUM VISITOR FLOW COUNTER\n";
    cout << "--------------------------------------------\n";
    do
    {
        cout << "\n=============== MAIN MENU ===============\n";
        cout << "1. Add visitor movement record\n";
        cout << "2. View all movement records\n";
        cout << "3. Display current visitor count\n";
        cout << "4. Exit\n";
        choice = readInteger("Enter your choice: ");
        switch (choice)
        {
        case 1:
            addRecord(records, recordCount, currentVisitors);
            break;
        case 2:
            viewRecords(records, recordCount);
            break;
        case 3:
            displayCurrentCount(currentVisitors);
            break;
        case 4:
            cout << "\nThank you for using Museum Visitor Flow Counter.\n";
            break;
        default:
            cout << "Invalid menu choice. Please select 1 to 4.\n";
        }
    } while (choice != 4);
    return 0;
}
