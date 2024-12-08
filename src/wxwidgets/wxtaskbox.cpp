#include "wxwidgets_lib/wxtaskbox.hpp"
#include <string> // for string and to_string()

WxTaskbox::WxTaskbox(wxWindow* parent, Map map) : wxDialog(parent, wxID_ANY, "Robot Task Assignment", wxDefaultPosition, wxSize(300, 300)) {
    // Define panel
    wxPanel* taskPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxSize(300, 300));
    // taskPanel->SetBackgroundColour(wxColor(255, 204, 229));

    // Sizer for entire panel
    wxBoxSizer* taskSizer = new wxBoxSizer(wxVERTICAL);

    // Add a text entry box to the panel
    //wxStaticText* label = new wxStaticText(taskPanel, wxID_ANY, "Enter Robot ID to Assign Rooms to Clean");
    //taskSizer->Add(label, 0, wxALL, 5);
    //textBox = new wxTextCtrl(taskPanel, wxID_ANY, "", wxDefaultPosition, wxSize(250, -1));
    //taskSizer->Add(textBox, 0, wxALL | wxEXPAND, 5);

    // Dynamically create checkboxes based on number of rooms in map
    for (int i = 1; i <= map.getNumRooms(); i++) {  
        std::string id = std::to_string(i);
        wxCheckBox* checkbox = new wxCheckBox(taskPanel, wxID_ANY, map.getRoomName(id)); 
        checkboxes.push_back(checkbox);
        taskSizer->Add(checkbox, 0, wxALL, 5);
    }

    // Set the sizer for the panel
    taskPanel->SetSizerAndFit(taskSizer);

    // Create a sizer for the entire dialog
    wxBoxSizer* dialogSizer = new wxBoxSizer(wxVERTICAL);
    dialogSizer->Add(taskPanel, 1, wxEXPAND | wxALL, 10);

    // Add OK and Cancel buttons directly to the dialog
    wxSizer* buttonSizer = CreateSeparatedButtonSizer(wxOK | wxCANCEL);
    dialogSizer->Add(buttonSizer, 0, wxEXPAND | wxALL, 10);

    // Set the dialog's sizer
    SetSizerAndFit(dialogSizer);
}

std::vector<bool> WxTaskbox::GetCheckboxStates() const {
    std::vector<bool> states;
    for (auto checkbox : checkboxes) {
        states.push_back(checkbox->IsChecked());
    }
    return states;
}

// Method to retrieve the text entered
//wxString WxTaskbox::GetTaskDescription() const {
//    return textBox->GetValue();
//}
