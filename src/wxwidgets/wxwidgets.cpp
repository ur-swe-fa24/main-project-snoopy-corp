#include "wxwidgets_lib/wxwidgets.hpp"
#include <ostream>

// Starts main application
bool MyWidget::OnInit() {
	MainFrame *MainWin = new MainFrame(_("Welcome to Snoopy Corp!"), wxDefaultPosition, wxSize(1000, 800));
	MainWin->Show(true);
	//SetTopWindow(MainWin); // set as the main window 
	return true;
} 

// EVENT TABLE: DEFINES EACH BUTTON / EVENT
BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( ID_Exit, MainFrame::OnExit ) 
    EVT_BUTTON ( ID_ToEngineer, MainFrame::switchToEngineer ) 
    EVT_BUTTON ( ID_ToManager, MainFrame::switchToManager ) 
    EVT_BUTTON ( ID_AddRobot, MainFrame::addRobot )
    EVT_BUTTON ( ID_DeleteRobot, MainFrame::deleteRobot )
END_EVENT_TABLE() 

// Properties of main window
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
: wxFrame((wxFrame *) NULL, -1, title, pos, size) 
{
    // Temporary, to be removed ------------------------------------------------------------------------------------------------------
    json roomsEx0 = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "Clean"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Tile"}}}
    };

    map = Map("map1", roomsEx0);
    simDriver = SimulationDriver(map);

    /*
    ShampooRobot robot = ShampooRobot(simDriver.assignRobotIndex(), map);
    simDriver.addRobot(robot);
    std::cout << "shampoo: " << robot.getId() << " " << robot.getLocation() << " " << robot.getBatteryLevel() << std::endl;
    
    ScrubberRobot newRobot = ScrubberRobot(simDriver.assignRobotIndex(), map);
    simDriver.addRobot(newRobot);
    std::cout << "scrubber" << newRobot.getId() << " " << newRobot.getLocation() << " " << newRobot.getBatteryLevel() << std::endl;

    std::cout << "first get fleet" << std::endl;
    json robotFleet = simDriver.getFleet();
    //std::cout << robotFleet << std::endl;
    */
    // ------------------------------------------------------------------------------------------------------------------------------
    
    
    // Defines main panel to hold everything
    wxPanel *mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    
    // Defines engineer screen and its contents
    engineerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    engineerPanel->SetBackgroundColour(wxColor(255, 204, 229));
    engineerTopPanel = new wxPanel(engineerPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    engineerBottomPanel = new wxPanel(engineerPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));

    // Create list for engineer panel to demonstrate robot information
    robotListView = new wxListView(engineerTopPanel);
    robotListView->AppendColumn("Id");
    robotListView->SetColumnWidth(0, 80);
    robotListView->AppendColumn("Type");
    robotListView->SetColumnWidth(1, 120);
    robotListView->AppendColumn("Status");
    robotListView->SetColumnWidth(2, 120);
    robotListView->AppendColumn("Location");
    robotListView->SetColumnWidth(3, 120);
    robotListView->AppendColumn("Battery Level");
    robotListView->SetColumnWidth(4, 120);
    robotListView->AppendColumn("Tasks Completed");
    robotListView->SetColumnWidth(5, 120);
    robotListView->AppendColumn("Current Room Status");
    robotListView->SetColumnWidth(6, 180);

    // Defines top half of engineer panel
    wxBoxSizer* engineerTopSizer = new wxBoxSizer(wxVERTICAL);
    engineerTopSizer->Add(robotListView, 1, wxALL | wxEXPAND, 0);
    engineerTopPanel->SetSizer(engineerTopSizer);

    // Defines bottom half of engineer panel
    wxBoxSizer* engineerBottomSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* addRobot = new wxButton(engineerBottomPanel, ID_AddRobot, "Add Robot");
    wxButton* deleteRobot = new wxButton(engineerBottomPanel, ID_DeleteRobot, "Delete Robot", wxPoint(50,50));
    engineerBottomSizer->Add(addRobot, 1, wxALL, FromDIP(10));
    engineerBottomSizer->Add(deleteRobot, 1, wxALL, FromDIP(10));
    engineerBottomPanel->SetSizer(engineerBottomSizer);

    //addRobotTest("Scrubber");
    populateList();

    // Pulls engineer screens together
    wxBoxSizer* engineerSizer = new wxBoxSizer(wxVERTICAL);
    wxButton* toManager = new wxButton(engineerPanel, ID_ToManager, "Go to Manager");
    engineerSizer->Add(toManager, 0, wxTOP | wxLEFT, 10);
    engineerSizer->Add(engineerTopPanel, 1, wxALL | wxEXPAND, 10);
    engineerSizer->Add(engineerBottomPanel, 1, wxALL | wxEXPAND, 10);
    engineerPanel->SetSizer(engineerSizer);

    // Defines manager screen and its contents
    managerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    managerPanel->SetBackgroundColour(wxColor(200, 204, 229));    

    wxBoxSizer* managerSizer = new wxBoxSizer(wxVERTICAL);
    wxButton* toEngineer = new wxButton(managerPanel, ID_ToEngineer, "Go to Engineer");
    managerSizer->Add(toEngineer, 0, wxTOP | wxLEFT, 10);
    managerPanel->SetSizer(managerSizer);

    // Create main sizer, add both screens
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(engineerPanel, 1, wxEXPAND);
    mainSizer->Add(managerPanel, 1, wxEXPAND);
    mainPanel->SetSizer(mainSizer);

    // Initially show engineer panel and hide manager panel
    engineerPanel->Show();
    managerPanel->Hide();
    mainSizer->Layout();
}
 
// Tells the OS to quit running this process
void MainFrame::OnExit( wxCommandEvent& event )
{
    Close(TRUE); 
}

// Button function to switch to engineer screen
void MainFrame::switchToEngineer(wxCommandEvent& event) {
    managerPanel->Hide();
    engineerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to switch to manager screen
void MainFrame::switchToManager(wxCommandEvent& event) {
    engineerPanel->Hide();
    managerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to add robot to list
void MainFrame::addRobot(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Must be Scrubber, Vacuum, or Shampoo", "Enter Robot Type");
    if (dialog.ShowModal() == wxID_OK) {
        if (!((dialog.GetValue()).ToStdString() == "Shampoo") && !((dialog.GetValue()).ToStdString() == "Scrubber") && !((dialog.GetValue()).ToStdString() == "Vacuum")) {
            
        } else {
            Robot robot = Robot(simDriver.stringToRobotType((dialog.GetValue()).ToStdString()), simDriver.assignRobotIndex());
            simDriver.addRobot(robot);

            json robotJson = robot.toJson();
            robotListView->InsertItem(integer, robotJson["ID"].dump());
            robotListView->SetItem(integer, 1, robotJson["Type"].dump());
            robotListView->SetItem(integer, 2, robotJson["Status"].dump());
            robotListView->SetItem(integer, 3, robotJson["Location"].dump());
            robotListView->SetItem(integer, 4, robotJson["Battery Level"].dump());
            robotListView->SetItem(integer, 5, robotJson["Tasks Completed"].dump());
            robotListView->SetItem(integer, 6, robotJson["Progress Task"].dump());
            integer++;
        }
    } else {

    }
}

// Button function to remove robot from list and simulation driver
void MainFrame::deleteRobot(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter robot ID to be removed", "Remove Robot");
    if (dialog.ShowModal() == wxID_OK) {
        int itemIndex = findListItem(dialog.GetValue());
        if (itemIndex != -1) {
            simDriver.removeRobot(stoi(dialog.GetValue().ToStdString()));
            robotListView->DeleteItem(itemIndex); // Delete the item
            wxMessageBox("Item with ID " + dialog.GetValue() + " deleted.", "Success");
        } else {
            wxMessageBox("Item with ID " + dialog.GetValue() + " not found.", "Error");
        }
    } else {
        //std::cout << "oh no" << std::endl;
    }
}

// Helper function for deleteRobot
int MainFrame::findListItem(wxString id) {
    int itemIndex = -1;
    int itemCount = robotListView->GetItemCount();

    for (int i = 0; i < itemCount; ++i) {
        if (robotListView->GetItemText(i, 0) == id) { // Compare with the ID in the first column
            itemIndex = i;
            break;
        }
    }
    return itemIndex;
}


// Temporary function to demonstrate list
void MainFrame::addRobotTest(wxString type) {
    robotListView->InsertItem(0, "1");
    robotListView->SetItem(0, 1, type);
    robotListView->SetItem(0, 2, "Active");
    robotListView->SetItem(0, 3, "0");
    robotListView->SetItem(0, 4, "10");
    robotListView->SetItem(0, 5, "2");
    robotListView->SetItem(0, 6, "None");
}

// Function that automatically populates list with robots in vector when wxPanel is first opened
// Might delete in upcoming sprint due to simulation driver constructor update (no longer needs robot vector?)
void MainFrame::populateList() {
    json robotFleet = simDriver.getFleet();

    for (int i = 0; i < robotFleet.size(); i++) {
        robotListView->InsertItem(i, robotFleet[i]["ID"].dump());
        robotListView->SetItem(i, 1, robotFleet[i]["Type"].dump());
        robotListView->SetItem(i, 2, robotFleet[i]["Status"].dump());
        robotListView->SetItem(i, 3, robotFleet[i]["Location"].dump());
        robotListView->SetItem(i, 4, robotFleet[i]["Battery Level"].dump());
        robotListView->SetItem(i, 5, robotFleet[i]["Tasks Completed"].dump());
        robotListView->SetItem(i, 6, robotFleet[i]["Progress Task"].dump());

    }
} 

