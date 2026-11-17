# Museum Visitor Flow Counter

A C++ console-based project developed for the CAP455 Object-Oriented Programming course. It records visitor entry and exit movements in a museum and keeps track of the current number of visitors inside.

## Features
- Add visitor movement records (ENTRY/EXIT).
- View all movement records.
- Prevent duplicate record IDs.
- Validate visitor details and visitor counts.
- Display the current visitor count.

## Technologies
- C++
- GCC Compiler
- Visual Studio Code

## How to Run

Compile:

```bash
g++ -std=c++11 src/CA1/38_CAP455_Phase1_Mueseum_visitor_flow_counter.cpp -o build/Museum_Visitor_Flow_Counter.exe
```

Run (Windows):

```powershell
.\build\Museum_Visitor_Flow_Counter.exe
```

## Current Phase
**CA1:** Uses an array of 50 objects and stores records in memory. Data is not saved after the program exits.

Further features will be added in the upcoming phases.
