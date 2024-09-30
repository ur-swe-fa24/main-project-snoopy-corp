# This is your design document's top level!

This is where the core designs are started.
You will also store your PlantUML source files in this directory.

### Use Case Diagram
![use_case](/docs/design/png_files/UseCaseDiagram.png)

The use case diagram highlights the epic level user stories of each actor. 

The Senior Management focus on two large use cases:
1. The dashboard display: Senior management should be able to use their dashboard to monitor error rates and utilization metrics across robots in real time, customize their dashboard by selecting important KPI's, and provide feedback.
2. View historical data trends: a log of robot and utilization metrics should be analyzed and presented somehow so management can identify patterns and predict future issues.

The Building Manager use cases focus more on managing robot fleets.
1. Viewing robot cleaning status of live robots to effectively manage the fleet.
2. Assign complex tasks to a single or  fleet of robots to address cleaning needs.

The Building Staff use cases focus on the every-day needs of robots.
1. Viewing robot status information such as battery level, water level, or location to address rising issues.
2. Quickly assign tasks to a single or fleet of robots to address sudden cleaning needs.

The Field Engineer use cases focus on the nitty-gritty robot needs.
1. Assign complex tasks to a single or  fleet of robots to address cleaning needs.
2. View status of live robots to debug and ensure proper operation.
3. Add and remove robots to a system so customers can purchase new robots.
4. View detailed error logs to debug properly.


### Class Diagram

[Class Diagram](CLASSES.md) - The class diagram shows the various objects that will be present in our project. 
