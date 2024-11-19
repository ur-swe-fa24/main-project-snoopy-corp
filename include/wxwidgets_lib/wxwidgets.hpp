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
    wxPanel *engineerPanel;
    wxPanel *engineerTopPanel;
    wxPanel *engineerBottomPanel;
    wxPanel *managerPanel;
    wxBoxSizer* mainSizer;
    wxListView *robotListView;

    Map map;
    SimulationDriver simDriver;

    void OnExit( wxCommandEvent& event ); //Exits program
    void switchToEngineer( wxCommandEvent& event ); // Switches screen to engineer perspective
    void switchToManager( wxCommandEvent& event ); // Switches screen to manager perspective
    void addRobot( wxCommandEvent& event ); // Add robot information to list
    void addRobotTest(wxString type);
    void populateList();
  
    DECLARE_EVENT_TABLE()
}; 

// Define unique IDs for buttons
enum {
    ID_ToManager = 1001,
    ID_ToEngineer = 1002,
    ID_AddRobot = 1003,
    ID_Exit = wxID_EXIT // You can reuse wxWidgets pre-defined IDs if needed
};

wxDECLARE_APP(MyWidget);

#endif
