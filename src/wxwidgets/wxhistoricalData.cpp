#include "wxwidgets_lib/wxhistoricalData.hpp"

WxHistoricalData::WxHistoricalData(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Historical Dashboard", wxDefaultPosition, wxSize(500, 350)) {
    // Create a panel inside the dialog
    wxPanel* historicalDashboard = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(500, 350));
    // historicalDashboard->SetBackgroundColour(wxColor(255, 204, 229));
    historicalListView = new wxListView(historicalDashboard);
    
    // Create list to show robot items
    historicalListView->AppendColumn("ID");
    historicalListView->SetColumnWidth(0, 80);
    historicalListView->AppendColumn("Tasks Attempted");
    historicalListView->SetColumnWidth(1, 120);
    historicalListView->AppendColumn("Tasks Completed");
    historicalListView->SetColumnWidth(2, 120);
    historicalListView->AppendColumn("Efficiency");
    historicalListView->SetColumnWidth(3, 120);

    wxBoxSizer* historicalViewSizer = new wxBoxSizer(wxVERTICAL);
    historicalViewSizer->Add(historicalListView, 1, wxALL | wxEXPAND, 10);
    historicalDashboard->SetSizer(historicalViewSizer);
}