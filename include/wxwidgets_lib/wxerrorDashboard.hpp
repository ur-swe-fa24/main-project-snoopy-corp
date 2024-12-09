// Error Dashboard Pop-Up Class
#ifndef WXERRORDASHBOARD_HPP
#define WXERRORDASHBOARD_HPP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "sim_lib/robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/robot.hpp"

class WxErrorDashboard : public wxDialog {
public:
    WxErrorDashboard(wxWindow* parent);

    wxListView *errorListView;
private:
    

};

#endif