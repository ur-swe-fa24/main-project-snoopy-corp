# Simulation Diagrams

![Simulation Diagrams](/docs/design/activity_diagrams/Simulator.png)

---

This diagram illustrates the core workflow of the `SimulationDriver` class, detailing the key decisions and actions that a user can take within the simulation. The diagram starts at the top with the initialization of the `SimulationDriver`, followed by a user interaction loop where different actions can be selected. Here’s an explanation of each part:

1. **Start of Simulation**: The simulation begins, and the system waits for user input. This input could involve several actions like adding a robot, removing a robot, viewing robot statuses, or interacting with the dashboard.

2. **Adding a Robot**: 
   - If the user decides to add a robot, the system asks for the type of robot (Scrubber, Shampoo, or Vacuum).
   - Depending on the chosen `robot_type`, the system creates the corresponding robot.
   - After creating the robot, the system adds it to the internal list of robots.

3. **Removing a Robot**:
   - If the user opts to remove a robot, the system first checks if the robot exists by searching for it using the robot ID.
   - If the robot is found, it is removed from the system.
   - If the robot is not found, the system notifies the user that the robot does not exist.

4. **Viewing the Dashboard**:
   - The user can open the dashboard to view the list of robots and their statuses.
   - The system prints the statuses of all robots.
   - After viewing, the user has the option to update a robot's status or provide feedback based on the system's output.
   - This loop continues as long as the user interacts with the dashboard, allowing them to view and update robot statuses multiple times before choosing to exit.

5. **Additional User Actions**: 
   - The diagram includes placeholders for further actions such as moving robots or initiating cleaning tasks (`Text 4`, `Text 5`).
   - These actions can trigger updates to robot statuses or their internal operations.

6. **Exiting the Simulation**:
   - At any point, the user can choose to exit the dashboard or the simulation entirely.
   - If the user opts to exit, the system terminates the process.
   - If no exit command is given, the simulation loop continues, allowing the user to keep interacting with the robots (adding, removing, viewing, or updating statuses).

The diagram illustrates a continuous loop where the system responds to user input, cycling through various robot-related actions until the user explicitly chooses to end the simulation.
