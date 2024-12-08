# Class Diagram
![class_diagram](/docs/design/png_files/class_diagram.png)

The UML diagram represents the design of a simulation and control system for robots, with components for database management, simulation drivers, a wxWidgets-based GUI, and specific robot types.

### Key Components:
1. **Simulation and Map Management**:
   - `SimulationDriver`: Core simulation engine handling robot interactions, map updates, and task scheduling.
   - `Map`: Represents the environment, supporting features like cleaning status and robot allocation.

2. **Robot Hierarchy**:
   - `Robot`: Base class defining shared robot attributes (e.g., ID, type, status) and behaviors.
   - Specialized robots: Includes `ScrubberRobot`, `ShampooRobot`, and `VacuumRobot`, each with specific functionalities.

3. **Database Management**:
   - `MongoDBWhisper`: Manages MongoDB connections, ensuring simulation data is stored and retrieved effectively.

4. **wxWidgets GUI and Dashboard**:
   - `MainFrame`: Central interface for user interaction, linking dashboards and data views.
   - Views include `WxDashboard`, `WxServiceData`, and `WxTaskbox`, each focusing on distinct operational aspects.

5. **Enums**:
   - Includes enumerations for robot types, states, and floor types, standardizing system variables.
