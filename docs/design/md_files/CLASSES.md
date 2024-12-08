# Class Diagram
![class_diagram](docs/design/modeling_diagrams/class_diagram.puml)

The class diagram shows the various objects that will be present in our project. 

The Simulation Driver stores the fleet of robots and serves as the main 'clock' via a thread implementation which will prompt the robots in the fleet to update (clean or move) and store their data in the MongoDB, and will prompt the MongoDBWrapper to push that data to the database.

The MainFrame class has three variants; the Live Robot Dashboard and Metrics Dashboard have information for their relevant staff, while the Error Log tracks Robot errors with the relevant info and time.

The MongoDBWrapper wraps the database which stores all of the dashboard's information on the back end. When prompted periodically by the Simulation Driver, it will refresh the visual dashboard's information.

MyWidget loads the app.

MainFrame handles the logic for the GUI, and incorporates it with the backend (adding, removing robots, etc). 

The closely related WxDashboard displays the availible robots.

The Map class contains the JSON map of the room as well as the status of each room by index.

The Robot class and its three children represent the actual robots.

Finally, the various enum types are used to represent objects in the real world (such as a robot's type, its current status, or the floor type).