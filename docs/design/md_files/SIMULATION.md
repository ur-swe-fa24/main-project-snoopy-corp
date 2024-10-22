# Simulation Diagrams

## Part I
![Simulation Diagrams Part I](/docs/design/activity_diagrams/Simulator.png)

This diagram illustrates the core workflow of the `SimulationDriver` class, detailing the key decisions and actions that a user can take within the simulation. The diagram starts at the top with the initialization of the `SimulationDriver`, followed by a user interaction loop where different actions can be selected. Here’s an explanation of each part:

1. **Start of Simulation**: The simulation begins, and the system waits for user input. This input could involve several actions like adding a robot, removing a robot, or interacting with the dashboard.
   
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
   - After viewing the dashboard, the user can either exit the dashboard or proceed to interact further with the simulation.

5. **Other User Actions**: 
   - The diagram also contains placeholders for additional user actions such as moving robots or initiating a cleaning action (`Text 4`, `Text 5`).
   - These interactions would trigger further updates to the robots' status or operations.

6. **Exit Simulation**:
   - At any point, the user can choose to exit the simulation. If the exit command is given, the simulation process ends.
   - If not, the loop continues and the system awaits further input from the user, such as adding, removing robots, or performing other actions.

The diagram demonstrates a looping structure where user inputs dictate the next step in the simulation, and the process can continue indefinitely until the user explicitly chooses to exit the simulation.

## Part II
![Simulation Diagrams Part II](/docs/design/activity_diagrams/............png)