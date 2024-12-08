#include "wxwidgets_lib/wxerrorDashboard.hpp"

WxErrorDashboard::WxErrorDashboard(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Error Dashboard", wxDefaultPosition, wxSize(860, 350)) {
    // Create a panel inside the dialog
    wxPanel* errorDashboard = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(860, 350));
    errorDashboard->SetBackgroundColour(wxColor(255, 204, 229));
    errorListView = new wxListView(errorDashboard);
    
    // Create list to show robot items
    errorListView->AppendColumn("Error Notes");
    errorListView->SetColumnWidth(0, 300);
    errorListView->AppendColumn("ID");
    errorListView->SetColumnWidth(0, 80);
    errorListView->AppendColumn("Location");
    errorListView->SetColumnWidth(0, 150);
    errorListView->AppendColumn("Time");
    errorListView->SetColumnWidth(0, 300);
    

    wxBoxSizer* errorViewSizer = new wxBoxSizer(wxVERTICAL);
    errorViewSizer->Add(errorListView, 1, wxALL | wxEXPAND, 10);
    errorDashboard->SetSizer(errorViewSizer);
}