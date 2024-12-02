// Start of wxWidgets Program
#ifndef WXDASHBOARD_HPP
#define WXDASHBOARD_HPP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "sim_lib/robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/robot.hpp"

class WxDashboard : public wxDialog {
public:
    WxDashboard(wxWindow* parent);

private:
    wxListView *robotListView;

};

#endif