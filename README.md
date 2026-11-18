# Museum Visitor Flow Counter

A C++ console-based project developed for the CAP455 Object-Oriented Programming course. It records visitor entry and exit movements in a museum and keeps track of the current number of visitors inside.

## Features
- Add visitor movement records (ENTRY/EXIT).
- View all movement records.
- Search records using record ID.
- Update existing records.
- Prevent duplicate record IDs.
- Validate visitor details and visitor counts.
- Display the current visitor count.
- Save records permanently using binary file handling.

## Technologies
- C++
- GCC Compiler
- Visual Studio Code
- File Handling (`fstream`)

## How to Run

### CA1

Compile:
```bash
g++ -std=c++11 src/CA1/38_CAP455_Phase1_Mueseum_visitor_flow_counter.cpp -o 38_CAP455_Phase1_Mueseum_visitor_flow_counter.exe
```

### CA2

Open the `src/CA2` folder in the terminal.

Compile:
```bash
g++ -std=c++11 -Wall -Wextra 38_CAP455_Phase2_Mueseum_visitor_flow_counter.cpp -o 38_CAP455_Phase2_Mueseum_visitor_flow_counter.exe
```

Run:
```powershell
.\38_CAP455_Phase2_Mueseum_visitor_flow_counter.exe
```

## Data Storage
CA1 stores records in memory, while CA2 uses a binary file named `visitor_records.dat` to save records permanently.

## Current Phase
- **CA1:** Completed – Basic visitor management using an array of objects.
- **CA2:** Completed – File handling, searching, updating and permanent data storage.

## Test Results
Test results for both phases are available in the `tests` folder.
