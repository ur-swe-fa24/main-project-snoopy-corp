#include "wxwidgets_lib/wxwidgets.hpp"
#include <ostream>

bool MyWidget::OnInit() {
	MainFrame *MainWin = new MainFrame(_("Welcome to Snoopy Corp!"), wxDefaultPosition, wxSize(1000, 800));
	MainWin->Show(true);
	//SetTopWindow(MainWin); // set as the main window 
	return true;
} 

BEGIN_EVENT_TABLE ( MainFrame, wxFrame )
    EVT_BUTTON ( ID_Exit, MainFrame::OnExit ) 
    EVT_BUTTON ( ID_ToEngineer, MainFrame::switchToEngineer ) 
    EVT_BUTTON ( ID_ToManager, MainFrame::switchToManager ) 
END_EVENT_TABLE() 


MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
: wxFrame((wxFrame *) NULL, -1, title, pos, size) 
{
    // Defines main panel to hold everything
    wxPanel *mainPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    
    // Defines engineer screen and its contents
    engineerPanel = new wxPanel(mainPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    engineerPanel->SetBackgroundColour(wxColor(255, 204, 229));
    
    engineerTopPanel = new wxPanel(engineerPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    //engineerTopPanel->SetBackgroundColour(wxColor(255, 194, 229));

    engineerBottomPanel = new wxPanel(engineerPanel, wxID_ANY, wxDefaultPosition, wxSize(100, 200));
    //engineerBottomPanel->SetBackgroundColour(wxColor(225, 204, 229)); 

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
    robotListView->AppendColumn("Map");
    robotListView->SetColumnWidth(5, 120);
    robotListView->AppendColumn("Current Room Status");
    robotListView->SetColumnWidth(6, 180);

    addRobot("Scrubber");

    wxBoxSizer* engineerTopSizer = new wxBoxSizer(wxVERTICAL);
    engineerTopSizer->Add(robotListView, 1, wxALL | wxEXPAND, 0);
    engineerTopPanel->SetSizer(engineerTopSizer);

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

void MainFrame::switchToEngineer(wxCommandEvent& event) {
    managerPanel->Hide();
    engineerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

void MainFrame::switchToManager(wxCommandEvent& event) {
    engineerPanel->Hide();
    managerPanel->Show();
    mainSizer->Layout(); // Update layout to reflect changes
}

void MainFrame::addRobot(wxString type) {
    robotListView->InsertItem(0, "1");
    robotListView->SetItem(0, 1, type);
    robotListView->SetItem(0, 2, "Active");
    robotListView->SetItem(0, 3, "0");
    robotListView->SetItem(0, 4, "10");
    robotListView->SetItem(0, 5, "Jepson");
    robotListView->SetItem(0, 6, "None");
}