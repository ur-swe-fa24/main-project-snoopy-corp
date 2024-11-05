#include <wx/wx.h>
#include <iostream>

class Test_Wx : public wxApp {
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame {
public:
    MyFrame() : wxFrame(nullptr, wxID_ANY, "Hello wxWidgets") {
        Show(true);
    }
};

wxIMPLEMENT_APP(Test_Wx);

bool Test_Wx::OnInit() {
    std::cout << "Init";
    wxLogMessage("Application is initializing...");
    MyFrame *frame = new MyFrame();
    frame->Show(true);
    return true;
}