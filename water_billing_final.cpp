#include <iostream>
#include <string>

class User {
    std::string username;
    std::string password;
    bool logged_in;
    float current_reading;
    float previous_reading;
    float total_cost;

public:
    User() : username("John"), password("password"), logged_in(false), current_reading(0), previous_reading(0), total_cost(0) {}

    bool login(std::string username, std::string password);
    void logout();
    bool is_logged_in() const;
    std::string get_username() const;

    void display_menu();
    float check_current_bill() const;
    void make_payment(float amount);
    void enter_meter_readings(float current_reading, float previous_reading);
};

// Login method to authenticate user
bool User::login(std::string username, std::string password) {
    if (this->username == username && this->password == password) {
        logged_in = true;
        return true;
    } else {
        return false;
    }
}

// Logout method to log out the user
void User::logout() {
    logged_in = false;
}

// Check if the user is logged in
bool User::is_logged_in() const {
    return logged_in;
}

// Get the username of the user
std::string User::get_username() const {
    return username;
}

// Display the menu of available options
void User::display_menu() {
    std::cout << "Select an option:" << std::endl;
    std::cout << "0: Check current bill" << std::endl;
    std::cout << "1: Make payment" << std::endl;
    std::cout << "2: Enter meter readings" << std::endl;
    std::cout << "3: Log out" << std::endl;
}

// Check the current bill of the user
float User::check_current_bill() const {
    // calculate the units consumed
    float units_consumed = previous_reading - current_reading;

    // calculate the total cost of the consumption
    float consumption_cost = (units_consumed * 5.50) + 300;
    float vat = 0.05 * consumption_cost;
    float total_cost = consumption_cost + vat;

    return total_cost;
}

// Make a payment on the user's account
void User::make_payment(float amount) {
    // reduce the user's total cost by the amount paid
    total_cost -= amount;

    std::cout << "Thank you for your payment. Your current outstanding balance is KES " << total_cost << "." << std::endl;
}

// Enter the user's meter readings
void User::enter_meter_readings(float current_reading, float previous_reading) {
    // validate the meter readings
    if (current_reading <= previous_reading) {
        std::cout << "Invalid meter readings. Please try again." << std::endl;
        return;
    }

    // update the user's meter readings
    this->current_reading = current_reading;
    this->previous_reading = previous_reading;

    std::cout << "Meter readings entered successfully." << std::endl;
}

int main() {
    User user;
    int login_attempts = 0;
    bool exit_program = false;

    while (!user.is_logged_in() && login_attempts < 3) {
        std::string username, password;
        std::cout << "Enter username: ";
        std::getline(std::cin >> std::ws, username);
        std::cout << "Enter password: ";
        std::getline(std::cin >> std::ws, password);

        if (user.login(username, password)) {
            std::cout << "Login successful. Welcome, " << user.get_username() << "!" << std::endl;
        } else {
            std::cout << "Invalid username or password. Please try again." << std::endl;
            login_attempts++;
        }
    }

    if (!user.is_logged_in()) {
        std::cout << "Maximum number of login attempts exceeded. Please try again later." << std::endl;
        return 0;
    }

    while (!exit_program) {
        user.display_menu();

        int option;
        std::cin >> option;

        switch (option) {
            case 0:
                std::cout << "Your current bill is KES " << user.check_current_bill() << "." << std::endl;
                break;
            case 1:
                float payment_amount;
                std::cout << "Enter payment amount: ";
                std::cin >> payment_amount;
                user.make_payment(payment_amount);
                break;
            case 2:
                float current_reading, previous_reading;
                std::cout << "Enter current meter reading: ";
                std::cin >> current_reading;
                std::cout << "Enter previous meter reading: ";
                std::cin >> previous_reading;
                user.enter_meter_readings(current_reading, previous_reading);
                break;
            case 3:
                std::cout << "Logging out. Goodbye, " << user.get_username() << "!" << std::endl;
                user.logout();
                exit_program = true;
                break;
            default:
                std::cout << "Invalid option selected. Please try again." << std::endl;
                break;
        }
    }

    return 0;
}
