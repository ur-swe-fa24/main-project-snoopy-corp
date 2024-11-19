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


### MongoDB Component:

@skyler-he