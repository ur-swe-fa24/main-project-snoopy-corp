# Snoopy Corp Cleaning Robot Fleet Management Software User Guide - Version 4.0
## Brett Barnes, Dhruvam Desai, Adelina Gutic, Skyler He

### Unit Testing:
To test speficic components:
1.  Build the project
2. Navigate to ~/main-project-snoopy-corp/build/tests
3. Run 'make'
4. Run the generated test binaries (e.g. ./clean_test)
5. All assertions should pass!

### Graphical Components:

To run wxWidgets:  
1. Build the project
2. Navigate to ~/main-project-snoopy-corp/build/app
3. Run 'make'
4. Run executable myWxExe to make it to GUI interface

Then, the interface will have an empty list, as well as an 'add robot' and 'delete robot' button.  
To run Add Robot:
1. Click button
2. Type in (note case-sensitivity) type of robot from list
3. Watch it be automatically added to the list!

To run Delete Robot:
1. Click button
2. Type in ID of existing robot to be removed
3. Watch it be automatically deleted from the list!




### User Guide for MongoDB Wrapper Functions

**Prerequisites**
1. Ensure MongoDB is running and accessible via the URI you provide.
2. Initialize a `MongoDBWrapper` instance with the database and collection names:
   ```cpp
   MongoDBWrapper dbWrapper(
       "mongodb://localhost:27017",  // MongoDB URI
       "robot_database",            // Database name
       "active_robots",             // Active robots collection name
       "removed_robots",            // Removed robots collection name
       "error_logs"                 // Error logs collection name
   );
   ```
3. Include the necessary libraries and set up logging with `spdlog`.

---

#### **1. Adding or Updating a Robot**
To add a new robot or update an existing robot's data, use the `upsertRobotData` method.

**Example Code**:
```cpp
nlohmann::json robotData = {
    // ID and Status are required
    {"ID", 1},
    {"Status", "Active"},
    // MongoDB's schema-less nature allows additional fields in documents, 
    // so any extra fields in the JSON will also be inserted or updated in the database.
    {"Location", "Room 1"},
    {"Battery Level", 85}
};

dbWrapper.upsertRobotData(robotData);
```

#### Description:
- If the robot with `ID` `1` does not exist in the database, it will be added to the **active_robots** collection.
- If the robot already exists, its data will be updated.
- The `Status` field determines whether the robot is active or removed.

---

### **2. Moving a Robot to the Removed Collection**
To move a robot from the active collection to the removed collection, use the `moveRobotToRemoved` method. This action indicates the robot is no longer in use but retains its data for record-keeping.

#### Example Code:
```cpp
int robotID = 1; // The ID of the robot to remove

dbWrapper.moveRobotToRemoved(robotID);
```

#### Description:
- The function searches for the robot with `ID` `1` in the **active_robots** collection.
- If found:
  - It modifies the `Status` field to `"Removed"`.
  - Adds the robot's data to the **removed_robots** collection.
  - Deletes the robot from the **active_robots** collection.
- If not found, it logs a warning.

---

### **3. Logging an Error (e.g., Robot Cleaning a Room)**
To log an error or event for a robot (e.g., cleaning failure in a specific room), use the `logError` method.

#### Example Code:
```cpp
nlohmann::json errorData = {
    {"Time", "2024-11-21 14:30:00"},  // Timestamp in ISO 8601 format
    {"ID", 101},                      // Robot ID
    {"Location", "Room 1"},           // Room where the event occurred
    {"ErrorNotes", "Failed to clean the room due to low battery."} // Error description
};

dbWrapper.logError(errorData);
```

#### Description:
- Logs the error to the **error_logs** collection in MongoDB.
- Required fields: `Time`, `ID`, `Location`, `ErrorNotes`.
- If any field is missing, the function logs an error message and exits.

