#include "wxwidgets_lib/wxhistoricalData.hpp"

WxHistoricalData::WxHistoricalData(wxWindow* parent) : wxDialog(parent, wxID_ANY, "Historical Dashboard", wxDefaultPosition, wxSize(1000, 700)) {
    // Create a panel inside the dialog
    wxPanel* historicalDashboard = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(1000, 700));
    historicalDashboard->SetBackgroundColour(wxColor(255, 204, 229));
    historicalListView = new wxListView(historicalDashboard);
    
    // Create list to show robot items
    historicalListView->AppendColumn("Id");
    historicalListView->SetColumnWidth(0, 80);
    historicalListView->AppendColumn("Type");
    historicalListView->SetColumnWidth(1, 120);
    historicalListView->AppendColumn("Status");
    historicalListView->SetColumnWidth(2, 120);
    historicalListView->AppendColumn("Location");
    historicalListView->SetColumnWidth(3, 120);
    historicalListView->AppendColumn("Battery Level");
    historicalListView->SetColumnWidth(4, 120);
    historicalListView->AppendColumn("Queue Length");
    historicalListView->SetColumnWidth(5, 120);
    historicalListView->AppendColumn("Current Room Status");
    historicalListView->SetColumnWidth(6, 180);

    wxBoxSizer* historicalViewSizer = new wxBoxSizer(wxVERTICAL);
    historicalViewSizer->Add(historicalListView, 1, wxALL | wxEXPAND, 10);
    historicalDashboard->SetSizer(historicalViewSizer);
}