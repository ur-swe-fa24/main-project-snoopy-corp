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
    EVT_BUTTON ( ID_UpdateRobot, MainFrame::updateRobot ) 
    EVT_CLOSE( MainFrame::OnClose )
END_EVENT_TABLE() 

// Properties of main window
MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
: wxFrame((wxFrame *) NULL, -1, title, pos, size)
{
    // To be modified ----------------------------------------------------
    json roomsEx0 = {
        {"1", {{"Room", "Kitchen"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Wood"}}},
        {"2", {{"Room", "Office"}, {"Cleaning Status", "Clean"}, {"FloorType", "Carpet"}}},
        {"3", {{"Room", "Bathroom"}, {"Cleaning Status", "Unclean"}, {"FloorType", "Tile"}}}
    };

    static mongocxx::instance instance{};
    map = Map("map1", roomsEx0);
    simDriver = SimulationDriver(map);
    simDriver.setMongoWrapper(mongo_wrapper);

    const auto f = [this](){
        while(!this->quitRequested){
            this->simDriver.update_all();
            this->refresh();
            std::this_thread::sleep_for (std::chrono::seconds(3));
        }
        return;
    };
    updateThread = std::thread{f};

    liveDashboard = new WxDashboard(this);

    // ------------------------------------------------------------------
    
    // Defines base panel to hold everything
    mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    
    // Main menu: Panel that will direct user based on selected job type
    mainMenu = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    mainMenu->SetBackgroundColour(wxColor(255, 104, 229));
    
    // Buttons on Main Menu to direct users to their job screens
    wxBoxSizer* mainMenuSizer = new wxBoxSizer(wxHORIZONTAL);
    wxButton* engineerButton = new wxButton(mainMenu, ID_ToEngineer, "Field Engineer");
    wxButton* staffButton = new wxButton(mainMenu, ID_ToStaff, "Building Staff");
    wxButton* managerButton = new wxButton(mainMenu, ID_ToManager, "Manager");
    wxButton* seniorManagerButton = new wxButton(mainMenu, ID_ToSeniorManager, "Senior Manager"); 

    // Pull Main Menu together
    mainMenuSizer->Add(engineerButton, 0, wxTOP | wxLEFT, 10);
    mainMenuSizer->Add(staffButton, 0, wxTOP | wxLEFT, 10);
    mainMenuSizer->Add(managerButton, 0, wxTOP | wxLEFT, 10);
    mainMenuSizer->Add(seniorManagerButton, 0, wxTOP | wxLEFT, 10);
    mainMenu->SetSizer(mainMenuSizer);

    // Defines engineer screen and its contents
    engineerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    engineerPanel->SetBackgroundColour(wxColor(255, 204, 229));
    wxButton* toLiveDashboard = new wxButton(engineerPanel, ID_ToLiveDashboard, "Go to Live Dashboard");
    wxButton* addRobot = new wxButton(engineerPanel, ID_AddRobot, "Add Robot");
    wxButton* deleteRobot = new wxButton(engineerPanel, ID_DeleteRobot, "Delete Robot", wxPoint(50,50));
    wxBoxSizer* engineerSizer = new wxBoxSizer(wxVERTICAL);
    engineerSizer->Add(toLiveDashboard, 0, wxTOP | wxLEFT, 10);
    engineerSizer->Add(addRobot, 1, wxALL, FromDIP(10));
    engineerSizer->Add(deleteRobot, 1, wxALL, FromDIP(10));
    engineerPanel->SetSizer(engineerSizer);

    // Defines manager screen and its contents
    managerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    managerPanel->SetBackgroundColour(wxColor(200, 204, 229));    
    wxBoxSizer* managerSizer = new wxBoxSizer(wxVERTICAL);
    managerPanel->SetSizer(managerSizer);

    // Create main sizer, add both screens
    mainSizer = new wxBoxSizer(wxVERTICAL);
    mainSizer->Add(mainMenu, 1, wxEXPAND);
    mainSizer->Add(engineerPanel, 1, wxEXPAND);
    mainSizer->Add(managerPanel, 1, wxEXPAND);
    mainPanel->SetSizer(mainSizer);

    // Initially show engineer panel and hide manager panel
    mainMenu->Show();
    engineerPanel->Hide();
    managerPanel->Hide();
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

// Button function to switch to engineer screen
void MainFrame::switchToEngineer(wxCommandEvent& event) {
    mainMenu->Hide();
    managerPanel->Hide();
    engineerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

// Button function to switch to staff screen
void MainFrame::switchToStaff(wxCommandEvent& event) {
    
}

// Button function to switch to manager screen
void MainFrame::switchToManager(wxCommandEvent& event) {
    
}

// Button function to switch to senior manager screen
void MainFrame::switchToSeniorManager(wxCommandEvent& event) {
   
}

// Button function to open Live Dashboard Pop-Up
void MainFrame::switchToLiveDashboard(wxCommandEvent& event) {
    liveDashboard->ShowModal();
}

// Button function to add robot to list
void MainFrame::addRobot(wxCommandEvent& event) {
    wxTextEntryDialog dialog(this, "Must be Scrubber, Vacuum, or Shampoo", "Enter Robot Type");
    if (dialog.ShowModal() == wxID_OK) {
        if (!((dialog.GetValue()).ToStdString() == "Shampoo") && !((dialog.GetValue()).ToStdString() == "Scrubber") && !((dialog.GetValue()).ToStdString() == "Vacuum")) {
            
        } else {
            Robot robot = Robot(simDriver.stringToRobotType((dialog.GetValue()).ToStdString()), 1);
            simDriver.addRobot(robot);

            json robotJson = robot.toJson();
            liveDashboard->robotListView->InsertItem(integer, robotJson["ID"].dump());
            liveDashboard->robotListView->SetItem(integer, 1, robotJson["Type"].dump());
            liveDashboard->robotListView->SetItem(integer, 2, robotJson["Status"].dump());
            liveDashboard->robotListView->SetItem(integer, 3, robotJson["Location"].dump());
            liveDashboard->robotListView->SetItem(integer, 4, robotJson["Battery Level"].dump());
            liveDashboard->robotListView->SetItem(integer, 5, robotJson["Tasks Completed"].dump());
            liveDashboard->robotListView->SetItem(integer, 6, robotJson["Progress Task"].dump());
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

// Refresh robot list to reflect current status
void MainFrame::refresh() {
    json robotFleet = simDriver.getFleet();

    for (int i = 0; i < robotFleet.size(); i++) {
        liveDashboard->robotListView->SetItem(i, 1, robotFleet[i]["Type"].dump());
        liveDashboard->robotListView->SetItem(i, 2, robotFleet[i]["Status"].dump());
        liveDashboard->robotListView->SetItem(i, 3, robotFleet[i]["Location"].dump());
        liveDashboard->robotListView->SetItem(i, 4, robotFleet[i]["Battery Level"].dump());
        liveDashboard->robotListView->SetItem(i, 5, robotFleet[i]["Tasks Completed"].dump());
        liveDashboard->robotListView->SetItem(i, 6, robotFleet[i]["Progress Task"].dump());
    }
}

void MainFrame::updateRobot(wxCommandEvent& event) {

}

