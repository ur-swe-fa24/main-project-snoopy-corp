// Assign Tasks Dialog box Pop-Up Class
#ifndef WXTASKBOX_HPP
#define WXTASKBOX_HPP
#include <wx/wx.h>
#include <vector>
#include "sim_lib/robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/robot.hpp"

class WxTaskbox : public wxDialog {
public:
    WxTaskbox(wxWindow* parent, Map map);
    std::vector<bool> GetCheckboxStates() const; // Return states of checkboxes
    //wxString GetTaskDescription() const; // Return value from textbox

private:
    std::vector<wxCheckBox*> checkboxes; // Store checkboxes for easy access
    //wxTextCtrl* textBox;

};

#endif