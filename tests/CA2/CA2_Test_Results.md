# CA2 – Test Results
## Project: Museum Visitor Flow Counter

**Phase:** CA2 – File Handling and Record Management

### 1. Functional Testing

| Test ID | Test Case | Expected Result | Actual Result | Status |
|---|---|---|---|---|
| TC01 | Add ENTRY record (5 visitors) | Record saved; count becomes 5 | Record saved; count was 5 | PASS |
| TC02 | Add EXIT record (2 visitors) | Record saved; count becomes 3 | Record saved; count was 3 | PASS |
| TC03 | View all records | Display all stored records | Both records displayed | PASS |
| TC04 | Search existing ID (101) | Display matching record | Record found | PASS |
| TC05 | Search non-existing ID (104) | Display not-found message | Record not found | PASS |
| TC06 | Update record ID 101 | Update record successfully | Record updated successfully | PASS |
| TC07 | Verify updated visitor count | Count becomes 4 | Count was 4 | PASS |
| TC08 | Restart application | Previously saved records remain available | Both records persisted | PASS |
| TC09 | Add duplicate record ID | Reject duplicate ID | Duplicate rejected | PASS |
| TC10 | Enter zero visitor count | Reject invalid count | Input rejected | PASS |
| TC11 | Enter negative visitor count | Reject invalid count | Input rejected | PASS |
| TC12 | EXIT more visitors than currently inside | Reject invalid EXIT movement | Movement rejected | PASS |
| TC13 | Enter invalid menu choice | Display invalid-choice message | Invalid choice handled | PASS |
| TC14 | Check total stored records | Display correct record count | 2 records displayed | PASS |

### 2. Final Stored Records

| Record ID | Visitor Label | Movement Type | Visitor Count | Gate |
|---|---|---|---|---|
| 101 | Visitor_A | ENTRY | 6 | Gate_1 |
| 102 | Visitor B | EXIT | 2 | Main_gate |

**Final current visitor count:** 4

**Total records stored:** 2

### 3. CA2 Features Verified

- Default, parameterized and copy constructors.
- Destructor implementation.
- Binary file handling using `fstream`.
- Saving and reading fixed-size records.
- Searching records using `seekg()`.
- Updating records using `seekp()`.
- Data persistence after application restart.
- Input validation and duplicate ID prevention.

### 4. Conclusion

The CA2 implementation was tested successfully. Record addition, viewing, searching, updating, binary file storage, data persistence and input validation worked as expected during testing.