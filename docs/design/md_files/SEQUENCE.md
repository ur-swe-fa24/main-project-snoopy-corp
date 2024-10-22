# Sequence Diagrams
The following Sequence Diagrams showcase the interactions between different components of the program that occur to realize the use cases.

## Viewing Robot and Task Status
<img align="right" width="400" height="650" src="png_files/SequenceDiagrams/view_status.png">

The following diagram on the right models how a regular user of the system, which includes Building Manager, Building Staff, and Field Engineer, may view the status of Robots or tasks at any given time.

The diagrams begin with a user starting the dashboard and selecting their view between a Robot or a task starting a branching.
+ **Viewing a Robot**: Dashboard requests data from the Robot to update the data being displayed. In the case that the Robot is dead, the dashboard indicates so but still pulls last available data from storage to display it.
+ **Viewing a Task**: Dashboard requests data from the storage where the task data is being stored by each of the live Robot dashboard. It compiles the task data and displays it.

Both diplays are updated and dynamically refreshed every two seconds to keep the information real-time. The last branch showcases the closure of Dashboard which closes the loop and activation of Dashboard.

<br><br><br><br><br><br><br>

## Task Assignment
<img align="right" width="390" height="750" src="png_files/SequenceDiagrams/task_assignment.png">

The following diagram on the right models how a cleaning task is issued or scheduled.

There are two main branches here dependent on who the user is and if they want to assign an immediate cleaning task for a single Robot or create a complicated/scheduled task. Here, complicated refers to any task that may require multiple Robots such as scrubber and vacuum Robots working together to achieve the task. Firstly, the Task Module always collects Robot status and displays them along with the upcoming task schedule so tasks are given appropriately. Here are the two branches:

+ **Simple Task**: This task may be assigned by either Building Staff or Building Manager or Field Engineer users who can simply select the Robot and place that they wish to clean. This then triggers the Cleaning Task Sequence for a Robot
+ **Complicated or Scheduled Task**: This task is only assigned by users at Building Manager or Field Engineer level. The process begins by the user requesting to set up a task. Then, dependent on user choosing manual or automated scheduling, relevant scheduling questions are asked. If automated scheduling is chosen, the module autmatically fills the Robots for the task. The updated task schedule is then returned. A wake-up call at scheduled time is given if task was scheduled for later and otherwise cleaning task sequence is triggered for the assigned Robots in the task.

<br><br><br><br><br><br>

## Cleaning Task
<img align="right" width="400" height="1200" src="png_files/SequenceDiagrams/cleaning_task.png">

The following image on the right depicts how a task is assigned to a Robot and executed. The sequence diagram has following components:
+ **Task Origination**: Describes that the task can originate from a user or the task module from a scheduled task. Note that though the Building Staff is specified as the user, it can also be the Building Manager or Field Engineer if they iniate the task
+ **Task Execution**: Task execution begins with a call on the relevant Robot which also triggers the live Robot Dashboard to activate. The Dashboard and Robot are kept active while the task is ongoing and have following branches:
    + **No Task Updates**: The Robot proceeds with normal cleaning with two processes in parallel
        +**Robot Cleaning**: Robot cleans while checking for task updates and recording its data in the Storage constantly
        + **Dashboard Updates**: In parallel, Dashboard also contantly pings Robot for task updates and store overall task data in the Storage while also displaying updated data. The data retrieval from Dashboard occurs every two seconds. If the Robot does not respond within 30 seconds or responds with an error message, the Dashboard retrieves latest Robot data from the storage while recording the error. Then, it proceeds to inform the User of the error and waits until response from User or the Robot.
    + **Robot Status Issue**: If the Robot has critical status issue such as low water or filled trash bag which impedes it from doing the task, it informs the Dashboard of the situation which conveys the message to the User. Then, the Robot proceeds to docking location until status is resolved.
    + **Task Update**: If a task update is given to Robot on task, then that update is passed to the Robot and Dashboard
    + **All Task Completed**: If the tasks have been completed for a Robot, the Robot informs the Dashboard, Task Module, and stores its data in Storage. It then proceeds to dock if there are no queued task and if there are, the robot proceeds to the queued tasks. The Dashboard finishes by notifying User of the completion of the Task by the Robot.

<br><br><br><br><br><br><br><br><br><br><br><br>

## Field Engineer
<img align="right" width="400" height="900" src="png_files/SequenceDiagrams/field_engineer.png">

The following diagram showcase the use cases of the Field Engineer where they may add or delete a robot or they can access the error logs.

+ **Adding a Robot**: The Field Engineer begins by requesting to add a Robot from the Robot Management Module. The Module gets connection details, connects to the Robot, and then asks the Engineer to set up Robot location and map. In our scope, the map is given and map creation is not covered, so the User responds with a map and Robot location. Those parameters are set up in the Robot, the Robot is added to Storage database, and the Robot setup/addition is complete.
+ **Deleting a Robot**: The Field Engineer can also request to delete a Robot where they select from a list of Robots to delete. The Robot is deactivated if it is still connected and then removed from the system. Any scheduled tasks of Robot are retrieved and reset. The deletion record is then saved in storage with the details of the process. Then, the Engineer is notified of successful deletion while also being sent the relevant task information if any scheduled tasks need to be rescheduled.
+ **View Error Logs**: The Engineer can also view error logs in addition to their other views on the Dashboard when they open the Dashboard. When they request the Log, they are asked for the requested maps or robots in question. The Dashboard then retrieves that data from the Storage and displays the data with charts.

<br><br><br><br><br><br><br><br><br><br><br>

## Senior Management
<img align="right" width="400" height="800" src="png_files/SequenceDiagrams/senior_management.png">

The following diagram showcase the use cases of the Senior Management where they can see the data on Robot usage, customize available KPIs, get historical data, or provide feedback.

+ **Viewing Robot Usage**: When the Dashboard is opened, the default view is data view where Dashboard gets Robot use and Error data from Storage for Display. These charts are updated every two seconds.
++ **Customize KPIs**: The User can also choose to customize KPIs where they can choose the metrics that they wish to see. The Dashboard takes them to update the charts that it displays.
++ **Request Historical Data**: The User can also request older data for selected criterias. The Dashboard pulls the requested data from Storage and displays that data.
++ **Provide Feedback**: If the User clicks to provide feedback, a feedback form is provided on screen to the User for them to fill out and provide feedback.
The final branch shows closure and deactivation of Dashboard.
