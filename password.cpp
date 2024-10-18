#include <iostream>
#include <string>
#include <random>
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Output.H>

class PassGenUI : public Fl_Window {
    private:
        Fl_Input *input;
        Fl_Output *output;
        Fl_Button *generate_button;
    public:
        PassGenUI() : Fl_Window(300, 200, "Password Generator") {
            // Input field for password length
            input = new Fl_Input(100, 50, 200, 30, "Length");
            
            // Output field for generated password
            output = new Fl_Output(100, 150, 200, 30, "Password");
            
            // Initialize button
            generate_button = new Fl_Button(100, 100, 200, 30, "Generate");
            
            // Set callback for the generate button
            generate_button->callback(button_callback, (void*)this);
        }

        // Function to generate a random password
        std::string generate_password(int length) {
            const char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 
                                    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 
                                    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '_'};
            std::string password;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<> distr(0, sizeof(symbols) - 1);
            
            for (int i = 0; i < length; i++) {
                password += symbols[distr(gen)];
            }
            return password;
        }

        // Static callback function
        static void button_callback(Fl_Widget* widget, void* data) {
            PassGenUI* ui = (PassGenUI*)data;
            
            // Get length from input field
            const char* length_str = ui->input->value();
            int length = std::atoi(length_str);  // Convert input to integer
            
            // Generate password if the length is valid
            if (length > 0) {
                std::string password = ui->generate_password(length);
                ui->output->value(password.c_str());  // Display password in output field
            } else {
                ui->output->value("Invalid length");  // Show error message if length is invalid
            }
        }
};

int main() {
    PassGenUI win;
    win.show();
    return Fl::run();
}
