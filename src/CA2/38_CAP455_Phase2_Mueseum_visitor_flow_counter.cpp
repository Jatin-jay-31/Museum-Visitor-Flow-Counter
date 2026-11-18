
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
using namespace std;

enum class MovementType { ENTRY, EXIT };
struct VisitorFileRecord {
    int recordID;
    char visitorLabel[50];
    int movementType;
    int visitorCount;
    char gateName[30];
};
class VisitorRecord {
private:
    int recordID;
    string visitorLabel;
    MovementType movementType;
    int visitorCount;
    string gateName;
    static int totalRecords;
public:
    VisitorRecord() : recordID(0), visitorLabel(""), movementType(MovementType::ENTRY), visitorCount(0), gateName("") {}
    VisitorRecord(int id, const string &label, MovementType type, int count, const string &gate)
        : recordID(id), visitorLabel(label), movementType(type), visitorCount(count), gateName(gate) {}
    VisitorRecord(const VisitorRecord &other)
        : recordID(other.recordID), visitorLabel(other.visitorLabel), movementType(other.movementType),
          visitorCount(other.visitorCount), gateName(other.gateName) {}
    ~VisitorRecord() {}
    void setDetails(int id, const string &label, MovementType type, int count, const string &gate) {
        recordID = id;
        visitorLabel = label;
        movementType = type;
        visitorCount = count;
        gateName = gate;
    }
    int getID() const { return recordID; }
    string getLabel() const { return visitorLabel; }
    MovementType getType() const { return movementType; }
    int getVisitorCount() const { return visitorCount; }
    string getGate() const { return gateName; }
    static void displayTotalRecords() {
        cout << "\nTotal movement records: " << totalRecords << '\n';
    }
    friend void displayRecord(const VisitorRecord &record);
};
int VisitorRecord::totalRecords = 0;
void displayRecord(const VisitorRecord &record) {
    cout << "\nRecord ID       : " << record.recordID
         << "\nVisitor/Group   : " << record.visitorLabel
         << "\nMovement Type   : " << (record.movementType == MovementType::ENTRY ? "ENTRY" : "EXIT")
         << "\nVisitor Count   : " << record.visitorCount
         << "\nGate Name       : " << record.gateName << '\n';
}
VisitorFileRecord convertToFileRecord(const VisitorRecord &record) {
    VisitorFileRecord fileRecord{};
    fileRecord.recordID = record.getID();
    strncpy(fileRecord.visitorLabel, record.getLabel().c_str(), sizeof(fileRecord.visitorLabel) - 1);
    fileRecord.movementType = (record.getType() == MovementType::ENTRY) ? 1 : 2;
    fileRecord.visitorCount = record.getVisitorCount();
    strncpy(fileRecord.gateName, record.getGate().c_str(), sizeof(fileRecord.gateName) - 1);
    return fileRecord;
}
VisitorRecord convertToVisitorRecord(const VisitorFileRecord &fileRecord) {
    MovementType type = (fileRecord.movementType == 1) ? MovementType::ENTRY : MovementType::EXIT;
    return VisitorRecord(fileRecord.recordID, fileRecord.visitorLabel, type, fileRecord.visitorCount, fileRecord.gateName);
}
int readInteger(const string &message) {
    string input;
    int value;
    while (true) {
        cout << message;
        getline(cin, input);
        stringstream ss(input);
        char extra;
        if (ss >> value && !(ss >> extra)) return value;
        cout << "Invalid input. Please enter a whole number.\n";
    }
}
string readNonEmptyString(const string &message) {
    string value;
    while (true) {
        cout << message;
        getline(cin, value);
        if (value.find_first_not_of(" \t") != string::npos) return value;
        cout << "This field cannot be empty. Please try again.\n";
    }
}
const string DATA_FILE = "../../data/visitor_records.dat";
bool ensureDataFile() {
    fstream file(DATA_FILE, ios::binary | ios::in);
    if (file) return true;
    ofstream createFile(DATA_FILE, ios::binary);
    return createFile.good();
}
int getRecordCount() {
    fstream file(DATA_FILE, ios::binary | ios::in);
    if (!file) return -1;
    file.seekg(0, ios::end);
    streamoff fileSize = file.tellg();
    if (fileSize < 0 || fileSize % sizeof(VisitorFileRecord) != 0) return -1;
    return static_cast<int>(fileSize / sizeof(VisitorFileRecord));
}
bool isDuplicateID(int id) {
    fstream file(DATA_FILE, ios::binary | ios::in);
    if (!file) return false;
    VisitorFileRecord fileRecord;
    while (file.read(reinterpret_cast<char*>(&fileRecord), sizeof(fileRecord))) {
        if (fileRecord.recordID == id) return true;
    }
    return false;
}
int calculateCurrentVisitors() {
    fstream file(DATA_FILE, ios::binary | ios::in);
    if (!file) return 0;
    int currentVisitors = 0;
    VisitorFileRecord fileRecord;
    while (file.read(reinterpret_cast<char*>(&fileRecord), sizeof(fileRecord))) {
        if (fileRecord.movementType == 1) currentVisitors += fileRecord.visitorCount;
        else if (fileRecord.movementType == 2) currentVisitors -= fileRecord.visitorCount;
    }
    return currentVisitors;
}
void addRecord() {
    const int MAX_RECORDS = 50;
    int recordCount = getRecordCount();
    if (recordCount == -1) {
        cout << "\nUnable to read record file.\n";
        return;
    }
    if (recordCount >= MAX_RECORDS) {
        cout << "\nRecord storage is full.\n";
        return;
    }
    cout << "\n========== ADD VISITOR MOVEMENT ==========\n";
    int id = readInteger("Enter record ID: ");
    if (id <= 0) {
        cout << "Record ID must be positive.\n";
        return;
    }
    if (isDuplicateID(id)) {
        cout << "Duplicate record ID. Record not added.\n";
        return;
    }
    string label = readNonEmptyString("Enter visitor/group label: ");
    cout << "\n1. ENTRY\n2. EXIT\n";
    int typeChoice = readInteger("Select movement type: ");
    if (typeChoice != 1 && typeChoice != 2) {
        cout << "Invalid movement type.\n";
        return;
    }
    MovementType type = (typeChoice == 1) ? MovementType::ENTRY : MovementType::EXIT;
    int people = readInteger("Enter number of visitors: ");
    if (people <= 0) {
        cout << "Visitor count must be greater than zero.\n";
        return;
    }
    string gate = readNonEmptyString("Enter gate/access point name: ");
    int currentVisitors = calculateCurrentVisitors();
    if (type == MovementType::EXIT && people > currentVisitors) {
        cout << "Exit rejected. Only " << currentVisitors << " visitor(s) are currently inside.\n";
        return;
    }
    VisitorRecord record(id, label, type, people, gate);
    VisitorFileRecord fileRecord = convertToFileRecord(record);
    ofstream file(DATA_FILE, ios::binary | ios::app);
    if (!file) {
        cout << "Unable to open record file.\n";
        return;
    }
    file.write(reinterpret_cast<const char*>(&fileRecord), sizeof(fileRecord));
    if (!file) {
        cout << "Error while saving record.\n";
        return;
    }
    file.close();
    cout << "\nRecord added and saved successfully.\n";
    cout << "Current visitors inside: " << calculateCurrentVisitors() << '\n';
}
void viewRecords() {
    if (!ensureDataFile()) {
        cout << "Unable to access record file.\n";
        return;
    }

    fstream file(DATA_FILE, ios::binary | ios::in);
    if (!file) {
        cout << "Unable to open record file.\n";
        return;
    }
    VisitorFileRecord fileRecord;
    int count = 0;
    cout << "\n========== ALL MOVEMENT RECORDS ==========\n";
    while (file.read(reinterpret_cast<char*>(&fileRecord), sizeof(fileRecord))) {
        if (fileRecord.movementType != 1 && fileRecord.movementType != 2) {
            cout << "Invalid record found in file.\n";
            break;
        }
        VisitorRecord record = convertToVisitorRecord(fileRecord);
        cout << "\n---------- Record " << ++count << " ----------";
        displayRecord(record);
    }
    if (count == 0) cout << "No records have been added yet.\n";
    cout << "\nTotal movement records: " << count << '\n';
    file.close();
}
void searchRecord() {
    int id = readInteger("\nEnter record ID to search: ");
    if (id <= 0) {
        cout << "Invalid record ID.\n";
        return;
    }
    fstream file(DATA_FILE, ios::binary | ios::in);
    if (!file) {
        cout << "Unable to open record file.\n";
        return;
    }
    int recordCount = getRecordCount();
    if (recordCount <= 0) {
        cout << "No records available.\n";
        file.close();
        return;
    }
    VisitorFileRecord fileRecord;
    for (int i = 0; i < recordCount; i++) {
        file.seekg(static_cast<streamoff>(i) * sizeof(VisitorFileRecord), ios::beg);
        if (!file.read(reinterpret_cast<char*>(&fileRecord), sizeof(fileRecord))) {
            cout << "Error reading record file.\n";
            file.close();
            return;
        }
        if (fileRecord.recordID == id) {
            cout << "\nRecord found successfully!\n";
            VisitorRecord record = convertToVisitorRecord(fileRecord);
            displayRecord(record);
            file.close();
            return;
        }
    }
    cout << "\nRecord with ID " << id << " not found.\n";
    file.close();
}
void updateRecord() {
    int id = readInteger("\nEnter record ID to update: ");
    if (id <= 0) {
        cout << "Invalid ID.\n";
        return;
    }
    fstream file(DATA_FILE, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "Unable to open file.\n";
        return;
    }
    VisitorFileRecord oldRecord;
    int position = -1, count = getRecordCount();
    if (count < 0) {
        cout << "Unable to read record file.\n";
        file.close();
        return;
    }
    for (int i = 0; i < count; i++) {
        file.seekg(static_cast<streamoff>(i) * sizeof(VisitorFileRecord), ios::beg);
        if (!file.read(reinterpret_cast<char*>(&oldRecord), sizeof(oldRecord))) break;
        if (oldRecord.recordID == id) {
            position = i;
            break;
        }
    }
    if (position == -1) {
        cout << "Record not found.\n";
        file.close();
        return;
    }
    cout << "\nCurrent record:\n";
    VisitorRecord current = convertToVisitorRecord(oldRecord);
    displayRecord(current);
    string label = readNonEmptyString("Enter new visitor label: ");
    if (label.length() > 49) {
        cout << "Label must be 49 characters or less.\n";
        file.close();
        return;
    }
    int typeChoice = readInteger("Enter movement type (1=ENTRY, 2=EXIT): ");
    if (typeChoice != 1 && typeChoice != 2) {
        cout << "Invalid movement type.\n";
        file.close();
        return;
    }
    int people = readInteger("Enter new visitor count: ");
    if (people <= 0) {
        cout << "Count must be positive.\n";
        file.close();
        return;
    }
    string gate = readNonEmptyString("Enter new gate name: ");
    if (gate.length() > 29) {
        cout << "Gate name must be 29 characters or less.\n";
        file.close();
        return;
    }
    int currentVisitors = calculateCurrentVisitors();
    int oldEffect = (oldRecord.movementType == 1) ? oldRecord.visitorCount : -oldRecord.visitorCount;
    int visitorsWithoutRecord = currentVisitors - oldEffect;
    if (typeChoice == 2 && people > visitorsWithoutRecord) {
        cout << "Cannot update: exit count exceeds current visitors.\n";
        file.close();
        return;
    }
    MovementType type = (typeChoice == 1) ? MovementType::ENTRY : MovementType::EXIT;
    VisitorRecord updated(id, label, type, people, gate);
    VisitorFileRecord newRecord = convertToFileRecord(updated);
    file.clear();
    file.seekp(static_cast<streamoff>(position) * sizeof(VisitorFileRecord), ios::beg);
    file.write(reinterpret_cast<const char*>(&newRecord), sizeof(newRecord));
    if (file) cout << "Record updated successfully!\n";
    else cout << "Error updating record.\n";
    file.close();
}
void displayCurrentCount() {
    cout << "\nCurrent visitors inside the museum: " << calculateCurrentVisitors() << '\n';
}
void displayTotalRecords() {
    int count = getRecordCount();
    if (count == -1) cout << "Unable to read record file.\n";
    else cout << "\nTotal records stored: " << count << '\n';
}
int main() {
    if (!ensureDataFile()) {
        cout << "Unable to access data file. Check the data folder.\n";
        return 1;
    }
    int choice;
    do {
        cout << "\n===== MUSEUM VISITOR FLOW COUNTER =====\n";
        cout << "1. Add Record\n2. View All Records\n3. Search Record\n4. Update Record\n";
        cout << "5. Display Current Visitors\n6. Display Total Records\n7. Exit\n";
        choice = readInteger("Enter your choice: ");
        switch (choice) {
            case 1: addRecord(); break;
            case 2: viewRecords(); break;
            case 3: searchRecord(); break;
            case 4: updateRecord(); break;
            case 5: displayCurrentCount(); break;
            case 6: displayTotalRecords(); break;
            case 7: cout << "Thank you for using the system!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);
    return 0;
}
