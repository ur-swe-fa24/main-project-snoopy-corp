# Cobotiq Interview Document

## Customer Roles
+ Senior management
+ Building Manager (supervisor of operator)
+ Operator (guy running it and cleaning it up)
+ Technician

## How much information should the management interface system give to each role? (Does a technician get a debug window?)
+ *Senior manager* - Coverage, cost, productivity and efficiency metrics (cost per cleaning per square foot, compare metrics between robot and human to ensure cost is saved)
+ *Building Manager* - Assign tasks to robot fleets; view current robot status
+ *Operator / Building Staff* - “How did this run perform?”; Pick one robot to clean this room.
+ *Technician* - Focus on errors and robot status

## Data that should be present in database
+ Error code
+ Square code
+ What time test occurred and the tasks involved
+ Percent of planned area is completed
+ Battery usage
+ Water usage
+ A notification of completion: “I know I did the job!”
+ Image of the map that shows the area cleaned
+ Building layout (which is provided by external file)
+ Relational database

## Simulation
Simulated robots should exhibit errors (This is done through probability and different error types)
*Three types of robots*: (Scrub, Vacuum, and Shampoo)
+ Scrub works on wood and tile
+ Shampoo works on carpet
+ Vacuum works on all floor types
*Three sizes of robots*: (Small, Medium, and Large) 
+ *determines runtime due to battery
Simulation will model a building, assigning a robot to a room(s)
+ Ex: One runs out of water, automatically assign another one to pick up the slack & fill in
Rooms will be binary (clean / dirty). Test error if room is still “dirty” after run
+ Building Manager will care about this

## Some attributes the Management System should have / be able to do
+ Management system should allow user to cancel what the robot is currently doing and move onto new, user inputted priority
+ Add events to manipulate where robots can or can’t go (add “event day” at a school so robot won’t go in auditorium) or to constrain spaces temporarily
+ With docking station, operator can schedule for daily cleaning times
+ *Mobile app*: When robot completes task, add to log of information in app
+ Should be able to interact live during mid-run from user end (e.g. head janitor at EKU)
However, updates/maintenance can be done during stationary, so while robot is charging

## Extra / Not Mandatory
+ *Cleaning settings!*: How hot the brush is, brush speed, water heat -> Cleaning modes
+ There should be interaction / communication between two robots (might not be relevant to management system)
+ Can robots cross from hardwood to carpet (different domain)
    + Manually yes (not relevant)
+ Traffic sensor that causes robot to clean more often in areas that are more often traversed by people (not relevant to management system)
