#include "wxwidgets_lib/wxwidgets.hpp"
#include <ostream>

// Starts main application
bool MyWidget::OnInit() {
	MainFrame *MainWin = new MainFrame(_("Welcome to Snoopy Corp!"), wxDefaultPosition, wxSize(550, 300));
	MainWin->Show(true);
	//SetTopWindow(MainWin); // set as the main window 
	return true;
} 

// EVENT TABLE: DEFINES EACH BUTTON / EVENT
BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( ID_Exit, MainFrame::OnExit ) 
    EVT_BUTTON ( ID_ToEngineer, MainFrame::switchToEngineer ) 
    EVT_BUTTON ( ID_ToStaff, MainFrame::switchToStaff ) 
    EVT_BUTTON ( ID_ToManager, MainFrame::switchToManager ) 
    EVT_BUTTON ( ID_ToSeniorManager, MainFrame::switchToSeniorManager ) 
    EVT_BUTTON ( ID_ToLiveDashboard, MainFrame::switchToLiveDashboard ) 
    EVT_BUTTON ( ID_AddRobot, MainFrame::addRobot )
    EVT_BUTTON ( ID_DeleteRobot, MainFrame::deleteRobot )
    EVT_BUTTON ( ID_AssignTasks, MainFrame::assignTasks )
    EVT_BUTTON ( ID_ViewHistoricalData, MainFrame::viewHistoricalData )
    EVT_BUTTON ( ID_FixRobot, MainFrame::fixRobot )
    EVT_BUTTON ( ID_GoHome, MainFrame::goHome )
    EVT_BUTTON ( ID_Feedback, MainFrame::feedback )
    EVT_CLOSE( MainFrame::OnClose )
END_EVENT_TABLE() 

// Properties of main window
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
: wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
    // To be modified ----------------------------------------------------
    json roomsEx0 = {
        // {"-1", {{"Room", "Home Base"}, {"Cleaning Status", "-1"}, {"FloorType", "Wood"}}},
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "4"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "8"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "5"}, {"FloorType", "Tile"}}},
        {"4", {{"Room", "Hallway"}, {"Cleaning Status", "3"}, {"FloorType", "Wood"}}}
    };

    static mongocxx::instance instance{};
    map = Map("map1", roomsEx0);
    simDriver = SimulationDriver(map);
    simDriver.setMongoWrapper(mongo_wrapper);

    const auto f = [this](){
        while(!this->quitRequested){
            this->simDriver.update_all();
            this->refresh();
            std::this_thread::sleep_for (std::chrono::seconds(5));
        }
        return;
    };
    updateThread = std::thread{f};

    liveDashboard = new WxDashboard(this);
    historicalDashboard = new WxHistoricalData(this);

    // ------------------------------------------------------------------
    
    // Defines base panel to hold everything
    mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    
    // Main menu: Panel that will direct user based on selected job type
    mainMenu = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    mainMenu->SetBackgroundColour(wxColor(155, 204, 229));
    
    // Buttons on Main Menu to direct users to their job screens
    wxBoxSizer* mainMenuSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* mmButtonSizer = new wxBoxSizer(wxHORIZONTAL);
    
    wxStaticText* staticText = new wxStaticText(mainMenu, wxID_ANY, "Select Your Current Role!", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont font(20, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    staticText->SetForegroundColour(*wxBLACK);
    staticText->SetFont(font);
    
    wxButton* engineerButton = new wxButton(mainMenu, ID_ToEngineer, "Field Engineer");
    wxButton* staffButton = new wxButton(mainMenu, ID_ToStaff, "Building Staff");
    wxButton* managerButton = new wxButton(mainMenu, ID_ToManager, "Manager");
    wxButton* seniorManagerButton = new wxButton(mainMenu, ID_ToSeniorManager, "Senior Manager"); 

    // Pull Main Menu together
    mainMenuSizer->Add(staticText, 0, wxEXPAND | wxALL, 10);
    mainMenuSizer->Add(mmButtonSizer, 0, wxEXPAND | wxALL, 10);
    mmButtonSizer->Add(engineerButton, 0, wxTOP | wxALL, 10);
    mmButtonSizer->Add(staffButton, 0, wxTOP | wxALL, 10);
    mmButtonSizer->Add(managerButton, 0, wxTOP | wxALL, 10);
    mmButtonSizer->Add(seniorManagerButton, 0, wxTOP | wxALL, 10);
    mainMenu->SetSizer(mainMenuSizer);


    // Defines engineer screen and its contents
    engineerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    engineerPanel->SetBackgroundColour(wxColor(255, 204, 229));
    
    wxButton* goHome = new wxButton(engineerPanel, ID_GoHome, "Home");
    wxButton* toLiveDashboard = new wxButton(engineerPanel, ID_ToLiveDashboard, "Live Dashboard");
    wxButton* addRobot = new wxButton(engineerPanel, ID_AddRobot, "Add Robot");
    wxButton* deleteRobot = new wxButton(engineerPanel, ID_DeleteRobot, "Delete Robot");
    wxButton* assignTasks = new wxButton(engineerPanel, ID_AssignTasks, "Assign Tasks");
    wxButton* fixRobot = new wxButton(engineerPanel, ID_FixRobot, "Fix Robot");
    wxBoxSizer* engineerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* engHorizontalSizer = new wxBoxSizer(wxHORIZONTAL);
    
    engHorizontalSizer->Add(toLiveDashboard, 0, wxALL, FromDIP(10));
    engHorizontalSizer->AddStretchSpacer(1);
    engHorizontalSizer->Add(goHome, 0, wxALL, FromDIP(10));
    engineerSizer->Add(engHorizontalSizer, 1, wxEXPAND | wxALL, FromDIP(10));
    engineerSizer->Add(addRobot, 1, wxALL, FromDIP(10));
    engineerSizer->Add(deleteRobot, 1, wxALL, FromDIP(10));
    engineerSizer->Add(assignTasks, 1, wxALL, FromDIP(10));
    engineerSizer->Add(fixRobot, 1, wxALL, FromDIP(10));
    engineerPanel->SetSizer(engineerSizer);

    // Defines manager screen and its contents
    managerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    managerPanel->SetBackgroundColour(wxColor(255, 194, 229));    
    
    wxButton* goHome1 = new wxButton(managerPanel, ID_GoHome, "Home");
    wxButton* assignTasks1 = new wxButton(managerPanel, ID_AssignTasks, "Assign Tasks");
    wxButton* toLiveDashboard1 = new wxButton(managerPanel, ID_ToLiveDashboard, "Live Dashboard");
    wxBoxSizer* managerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* horzManagerSizer = new wxBoxSizer(wxHORIZONTAL);
    
    horzManagerSizer->Add(toLiveDashboard1, 0, wxALL, FromDIP(10));
    horzManagerSizer->AddStretchSpacer(1);
    horzManagerSizer->Add(goHome1, 0, wxALL, FromDIP(10));
    managerSizer->Add(horzManagerSizer, 1, wxEXPAND | wxALL, FromDIP(10));
    managerSizer->Add(assignTasks1, 1, wxALL, FromDIP(10));
    managerPanel->SetSizer(managerSizer);

    // Defines staff screen and its contents
    staffPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    staffPanel->SetBackgroundColour(wxColor(255, 184, 229));    
    
    wxButton* goHome2 = new wxButton(staffPanel, ID_GoHome, "Home");
    wxButton* assignTasks2 = new wxButton(staffPanel, ID_AssignTasks, "Assign Tasks");
    wxButton* toLiveDashboard2 = new wxButton(staffPanel, ID_ToLiveDashboard, "Live Dashboard");
    wxBoxSizer* staffSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* horzStaffSizer = new wxBoxSizer(wxHORIZONTAL);
    
    horzStaffSizer->Add(toLiveDashboard2, 0, wxALL, FromDIP(10));
    horzStaffSizer->AddStretchSpacer(1);
    horzStaffSizer->Add(goHome2, 0, wxALL, FromDIP(10));
    staffSizer->Add(horzStaffSizer, 1, wxEXPAND | wxALL, FromDIP(10));
    staffSizer->Add(assignTasks2, 1, wxALL, FromDIP(10));
    staffPanel->SetSizer(staffSizer);

    // Defines senior manager screen and its contents
    seniorManagerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    seniorManagerPanel->SetBackgroundColour(wxColor(200, 204, 229));    
    wxButton* viewHistorical = new wxButton(seniorManagerPanel, ID_ViewHistoricalData, "View Historical Data");
    wxButton* goHome3 = new wxButton(seniorManagerPanel, ID_GoHome, "Home");
    wxButton* feedback = new wxButton(seniorManagerPanel, ID_Feedback, "Give Feedback");
    wxBoxSizer* seniorManagerSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer* horzSeniorManagerSizer = new wxBoxSizer(wxHORIZONTAL);

    horzSeniorManagerSizer->Add(viewHistorical, 1, wxALL, FromDIP(10));
    horzSeniorManagerSizer->AddStretchSpacer(1);
    horzSeniorManagerSizer->Add(goHome3, 0, wxALL, FromDIP(10));
    seniorManagerSizer->Add(horzSeniorManagerSizer, 1, wxEXPAND | wxALL, FromDIP(10));
    seniorManagerSizer->Add(feedback, 0, wxTOP | wxALL, FromDIP(10));
    seniorManagerPanel->SetSizer(seniorManagerSizer);

    // Create main sizer, add both screens
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(mainMenu, 1, wxEXPAND);
    mainSizer->Add(engineerPanel, 1, wxEXPAND);
    mainSizer->Add(staffPanel, 1, wxEXPAND);
    mainSizer->Add(managerPanel, 1, wxEXPAND);
    mainSizer->Add(seniorManagerPanel, 1, wxEXPAND);
    mainPanel->SetSizer(mainSizer);

    // Initially show engineer panel and hide manager panel
    mainMenu->Show();
    engineerPanel->Hide();
    staffPanel->Hide();
    managerPanel->Hide();
    seniorManagerPanel->Hide();
    mainSizer->Layout();
}


// ---------- Private Methods --------------------------------------


// Tells the OS to quit running this process
void MainFrame::OnExit( wxCommandEvent& event )
{
    Close(TRUE); 
}

// Modifies default closing procedures to add thread cleanup
void MainFrame::OnClose(wxCloseEvent& event){
    // Disable the Frame and Stop the Update Thread before closing
    Disable();
    quitRequested.store(true);
    updateThread.join();
    event.Skip();
}

// Button function to return to home screen
void MainFrame::goHome(wxCommandEvent& event) {
    mainMenu->Show();
    engineerPanel->Hide();
    staffPanel->Hide();
    managerPanel->Hide();
    seniorManagerPanel->Hide();
    mainSizer->Layout();
}

// Button function to switch to engineer screen
void MainFrame::switchToEngineer(wxCommandEvent& event) {
    mainMenu->Hide();
    managerPanel->Hide();
    seniorManagerPanel->Hide();
    staffPanel->Hide();
    engineerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to switch to staff screen
void MainFrame::switchToStaff(wxCommandEvent& event) {
    mainMenu->Hide();
    managerPanel->Hide();
    engineerPanel->Hide();
    seniorManagerPanel->Hide();
    staffPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to switch to manager screen
void MainFrame::switchToManager(wxCommandEvent& event) {
    mainMenu->Hide();
    seniorManagerPanel->Hide();
    staffPanel->Hide();
    engineerPanel->Hide();
    managerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to switch to senior manager screen
void MainFrame::switchToSeniorManager(wxCommandEvent& event) {
    mainMenu->Hide();
    staffPanel->Hide();
    engineerPanel->Hide();
    managerPanel->Hide();
    seniorManagerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to open Live Dashboard Pop-Up
void MainFrame::switchToLiveDashboard(wxCommandEvent& event) {
    liveDashboard->Show();
}

// Button function to assign tasks to a robot
void MainFrame::assignTasks(wxCommandEvent& event) {
    // Create the dialog and pass the number of checkboxes
    WxTaskbox dialog(this, map);

    if (dialog.ShowModal() == wxID_OK) {
        // Retrieve checkbox states
        std::vector<bool> states = dialog.GetCheckboxStates();

        std::vector<int> tasks = {};
        for (int i = 0; i < map.getNumRooms(); i++) {
            if (states[i] == 1) {
                tasks.insert(tasks.end(), i+1); // Adding room id to tasks vector : Note ids start at 1, not 0
            }
        }

        simDriver.assignmentModule(tasks);
    }
}

// Button function to open historical data (removed robots)
void MainFrame::viewHistoricalData(wxCommandEvent& event) {
    //json removed = mongo_wrapper.getAllDataAsJson("removed");
    historicalDashboard->Show();

}

// Button function to add robot to list
void MainFrame::addRobot(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Must be Scrubber, Vacuum, or Shampoo", "Enter Robot Type");
    if (dialog.ShowModal() == wxID_OK) {
        if (!((dialog.GetValue()).ToStdString() == "Shampoo") && !((dialog.GetValue()).ToStdString() == "Scrubber") && !((dialog.GetValue()).ToStdString() == "Vacuum") && !((dialog.GetValue()).ToStdString() == "Error")) {
            
        } else {
            Robot robot;
            if ((dialog.GetValue()).ToStdString() == "Error") {
                robot = Robot(simDriver.stringToRobotType("Vacuum"), 1, 1);
            } else {
                robot = Robot(simDriver.stringToRobotType((dialog.GetValue()).ToStdString()), 1);
            }
            simDriver.addRobot(robot);

            json robotJson = robot.toJson();
            
            // Live Dashboard
            liveDashboard->robotListView->InsertItem(integer, robotJson["ID"].dump());
            liveDashboard->robotListView->SetItem(integer, 1, robotJson["Type"].dump());
            liveDashboard->robotListView->SetItem(integer, 2, robotJson["Status"].dump());
            if(robotJson["Location"].dump() == "-1")
                liveDashboard->robotListView->SetItem(integer, 3, "Charging Station");
            else
                liveDashboard->robotListView->SetItem(integer, 3, map.getRoomName(robotJson["Location"].dump()));
            liveDashboard->robotListView->SetItem(integer, 4, robotJson["Battery Level"].dump());
            liveDashboard->robotListView->SetItem(integer, 5, robotJson["Queue Length"].dump());
             if(robotJson["Location"].dump() == "-1")
                liveDashboard->robotListView->SetItem(integer, 6, "N/A");
            else
                liveDashboard->robotListView->SetItem(integer, 6, simDriver.getSelectedMap().getRoomCleanliness(robotJson["Location"].dump()));

            // Historical Dashboard
            historicalDashboard->historicalListView->InsertItem(integer, robotJson["ID"].dump());
            wxString mystring = wxString::Format(wxT("%i"), robot.getTC());
            historicalDashboard->historicalListView->SetItem(integer, 1, mystring);
            historicalDashboard->historicalListView->SetItem(integer, 2, robotJson["Task attempted"].dump());
            wxString mystring1 = wxString::Format(wxT("%f"), robot.getEfficiency());
            historicalDashboard->historicalListView->SetItem(integer, 1, mystring1);

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
            liveDashboard->robotListView->DeleteItem(itemIndex); // Delete the item
            historicalDashboard->historicalListView->DeleteItem(itemIndex);
            integer--;
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
    int itemCount = liveDashboard->robotListView->GetItemCount();

    for (int i = 0; i < itemCount; ++i) {
        if (liveDashboard->robotListView->GetItemText(i, 0) == id) { // Compare with the ID in the first column
            itemIndex = i;
            break;
        }
    }
    return itemIndex;
}

// Button function to fix robot
void MainFrame::fixRobot(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Enter robot ID to be fixed", "Fix Robot");
    if (dialog.ShowModal() == wxID_OK) {
        int id = std::stoi(std::string((dialog.GetValue()).mb_str()));
        int number = simDriver.fixRobot(id);
    }
}

// Refresh robot list to reflect current status
void MainFrame::refresh() {
    json robotFleet = simDriver.getFleet();
    for (int i = 0; i < robotFleet.size(); i++) {
        
        // Live Dashboard
        liveDashboard->robotListView->SetItem(i, 1, robotFleet[i]["Type"].dump());
        liveDashboard->robotListView->SetItem(i, 2, robotFleet[i]["Status"].dump());
        if(robotFleet[i]["Location"].dump() == "-1")
            liveDashboard->robotListView->SetItem(i, 3, "Charging Station");
        else
            liveDashboard->robotListView->SetItem(i, 3, map.getRoomName(robotFleet[i]["Location"].dump()));
        liveDashboard->robotListView->SetItem(i, 4, robotFleet[i]["Battery Level"].dump());
        liveDashboard->robotListView->SetItem(i, 5, robotFleet[i]["Queue Length"].dump()); 
        if(robotFleet[i]["Location"].dump() == "-1")
                    liveDashboard->robotListView->SetItem(i, 6, "N/A");
        else
            liveDashboard->robotListView->SetItem(i, 6, simDriver.getSelectedMap().getRoomCleanliness(robotFleet[i]["Location"].dump()));

        // Historical Dashboard
        historicalDashboard->historicalListView->InsertItem(i, robotFleet[i]["ID"].dump());
        wxString mystring = wxString::Format(wxT("%i"), simDriver.getRobot(stoi(robotFleet[i]["ID"].dump()))->getTC());
        historicalDashboard->historicalListView->SetItem(i, 1, mystring);
        historicalDashboard->historicalListView->SetItem(i, 2, robotFleet[i]["Task attempted"].dump());
        wxString mystring1 = wxString::Format(wxT("%f"), simDriver.getRobot(stoi(robotFleet[i]["ID"].dump()))->getEfficiency());
        historicalDashboard->historicalListView->SetItem(i, 1, mystring1);
    }
}

void MainFrame::feedback( wxCommandEvent& event ) {
    wxTextEntryDialog dialog(this, "How can we improve our services?", "Send in Feedback");
    if (dialog.ShowModal() == wxID_OK) {
        std::cout << "Thank you for your feedback!" << std::endl;
        std::cout << dialog.GetValue() << std::endl;
    }
}