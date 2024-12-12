// Utilization / Historical Dashboard Pop-Up Class
#ifndef WXHISTORICALDATA_HPP
#define WXHISTORICALDATA_HPP
#include <wx/wx.h>
#include <wx/listctrl.h>
#include "sim_lib/robot.hpp"
#include "sim_lib/simulation_driver.hpp"
#include "sim_lib/shampoo_robot.hpp"
#include "sim_lib/scrubber_robot.hpp"
#include "sim_lib/robot.hpp"

class WxHistoricalData : public wxDialog {
public:
    WxHistoricalData(wxWindow* parent);

    wxListView *historicalListView;
private:
    

};

#endif