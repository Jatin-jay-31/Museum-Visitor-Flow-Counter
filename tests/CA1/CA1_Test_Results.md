# CA1 – Test Results

**Project:** Museum Visitor Flow Counter  
**Language:** C++  
**Phase:** CA1 – In-Memory Record Management

## Test Cases

| Test ID | Test Description | Input / Test Condition | Expected Result | Actual Result | Status |
|---|---|---|---|---|---|
| TC01 | Add ENTRY record | Valid ID, visitor details, ENTRY, count = 10 | Record added and visitor count increases to 10 | Record added successfully.
Current visitors inside: 10 | PASS |
| TC02 | Add EXIT record | Valid ID, EXIT, count = 3 (current count = 10) | Record added and visitor count decreases to 7 | Record added successfully.
Current visitors inside: 7 | PASS |
| TC03 | Duplicate record ID | Enter an existing record ID | Duplicate record rejected | Duplicate record ID. Record not added. | PASS |
| TC04 | Invalid record ID | Enter ID = 0 or a negative ID | Invalid ID rejected | Record ID must be positive. | PASS |
| TC05 | Invalid visitor count | Enter count = 0 or a negative count | Invalid count rejected | Visitor count must be greater than zero. | PASS |
| TC06 | Excessive EXIT | Current count = 7; attempt EXIT of 10 | EXIT rejected and count remains unchanged | Exit rejected: only 7 visitor(s) are currently inside. | PASS |
| TC07 | View empty records | Select View Records without adding records | Appropriate no-records message displayed | No records have been added yet. | PASS |
| TC08 | Empty visitor details | Enter blank visitor label or gate name | Empty input rejected | This field cannot be empty. Please try again. | PASS |
| TC09 | Maximum capacity | Add 50 records, then attempt record 51 | Additional record rejected | Record storage is full. | PASS |
| TC10 | Invalid menu choice | Enter an invalid menu option | Invalid choice message displayed | Invalid menu choice. Please select 1 to 4. | PASS |

## Testing Notes

- Tests are performed using the CA1 console application.
- Records are stored in an array of 50 objects.
- Data is stored in memory and is cleared when the program exits.
- Actual results and status are updated after executing each test.