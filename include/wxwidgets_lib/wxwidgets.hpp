// Start of wxWidgets Program
#ifndef WXWIDGETS_HPP
#define WXWIDGETS_HPP
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>
#include "sim_lib/robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/robot.hpp"
#include "wxdashboard.hpp"
#include "database/mongoDBWrapper.hpp"

// Container class for the window, or frame in MainFrame
class MyWidget: public wxApp {
public:
	virtual bool OnInit(); 
};

// MainFrame is our window; a customized class derived from wxFrame
class MainFrame: public wxFrame { 
public: 
	MainFrame(const wxString &title, const wxPoint &pos, const wxSize &size); 

private:
    wxPanel *mainPanel;
    wxPanel *mainMenu;
    wxPanel *engineerPanel;
    wxPanel *engineerTopPanel;
    wxPanel *engineerBottomPanel;
    wxPanel *managerPanel;
    wxBoxSizer* mainSizer;
    wxListView *robotListView;
    WxDashboard* liveDashboard;

    Map map;
    MongoDBWrapper mongo_wrapper = MongoDBWrapper("mongodb://localhost:27017", "Robots", "active_robots", "removed_robots", "error_log");
    SimulationDriver simDriver;
    std::atomic<bool> quitRequested{false};
    std::thread updateThread;
    int integer = 0;

    void OnClose(wxCloseEvent &e); // Close the Frame
    void OnExit( wxCommandEvent& event ); //Exits program
    
    void switchToEngineer( wxCommandEvent& event ); // Switches screen to engineer perspective
    void switchToStaff ( wxCommandEvent& event ); // Switches screen to staff perspective
    void switchToManager ( wxCommandEvent& event ); // Switches screen to manager perspective
    void switchToSeniorManager ( wxCommandEvent& event ); // Switches screen to senior manager perspective
    void switchToLiveDashboard( wxCommandEvent& event ); // pops up live dashboard
    
    void addRobot( wxCommandEvent& event ); // Add robot information to list
    void deleteRobot( wxCommandEvent& event ); // Delete robot from list and simulation driver
    int findListItem( wxString id ); // Private helper function for deleteRobot
    void refresh(); // Refresh robot list to reflect current status
    void updateRobot( wxCommandEvent& event ); 


    DECLARE_EVENT_TABLE()
}; 

// Define unique IDs for buttons
enum {
    ID_ToLiveDashboard = 1001,
    ID_ToEngineer = 1002,
    ID_ToStaff = 1003,
    ID_ToManager = 1004,
    ID_ToSeniorManager = 1005,
    ID_AddRobot = 1006,
    ID_DeleteRobot = 1007,
    ID_UpdateRobot = 1008,
    ID_Exit = wxID_EXIT // You can reuse wxWidgets pre-defined IDs if needed
};

wxDECLARE_APP(MyWidget);

#endif
