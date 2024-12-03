#include "wxwidgets_lib/wxdashboard.hpp"

WxDashboard::WxDashboard(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Live Robot Dashboard", wxDefaultPosition, wxSize(1000, 700)) {
    // Create a panel inside the dialog
    wxPanel* liveDashboard = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1000, 700));
    liveDashboard->SetBackgroundColour(wxColor(255, 204, 229));
    robotListView = new wxListView(liveDashboard);
    
    // Create list to show robot items
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
    wxBoxSizer* robotViewSizer = new wxBoxSizer(wxVERTICAL);
    robotViewSizer->Add(robotListView, 1, wxALL | wxEXPAND, 10);
    liveDashboard->SetSizer(robotViewSizer);
}