#include "Intern.hpp"
#include "AForm.hpp"

int main() {
    {
        Intern intern;

        std::cout << "======== INTERN FORM CREATION TESTS ========\n";

        // TEST 1: Valid Form - RobotomyRequestForm
        std::cout << "\n[TEST 1] Robotomy Request Form Creation" << std::endl;
        AForm* form1 = intern.makeForm("robotomy request", "Bender");
        if (form1) delete form1;

        // TEST 2: Valid Form - ShrubberyCreationForm
        std::cout << "\n[TEST 2] Shrubbery Creation Form Creation" << std::endl;
        AForm* form2 = intern.makeForm("shrubbery creation", "Garden");
        if (form2) delete form2;

        // TEST 3: Valid Form - PresidentialPardonForm
        std::cout << "\n[TEST 3] Presidential Pardon Form Creation" << std::endl;
        AForm* form3 = intern.makeForm("presidential pardon", "Fry");
        if (form3) delete form3;

        // TEST 4: Invalid Form Name
        std::cout << "\n[TEST 4] Invalid Form Name" << std::endl;
        AForm* form4 = intern.makeForm("time travel request", "Doc Brown");
        if (form4) delete form4;

        // TEST 5: Case Sensitivity Check
        std::cout << "\n[TEST 5] Case Sensitivity Check" << std::endl;
        AForm* form5 = intern.makeForm("Robotomy Request", "Leela"); // Incorrect case
        if (form5) delete form5;

        // TEST 6: Empty Form Name
        std::cout << "\n[TEST 6] Empty Form Name" << std::endl;
        AForm* form6 = intern.makeForm("", "Nobody");
        if (form6) delete form6;

        // TEST 7: Empty Target with Valid Form
        std::cout << "\n[TEST 7] Empty Target with Valid Form" << std::endl;
        AForm* form7 = intern.makeForm("shrubbery creation", "");
        if (form7) delete form7;

        // TEST 8: Garbage Input
        std::cout << "\n[TEST 8] Garbage Input" << std::endl;
        AForm* form8 = intern.makeForm("!!!@@@###", "???");
        if (form8) delete form8;

        std::cout << "\n======== END OF TESTS ========\n";
    }
    {
        std::cout << "\n[CANONICAL FORM TESTS]\n";

        // 1. Default constructor
        Intern intern1;
        std::cout << "Default constructor called.\n";

        // 2. Copy constructor
        Intern intern2(intern1);
        std::cout << "Copy constructor called.\n";

        // 3. Copy assignment operator
        Intern intern3;
        intern3 = intern1;
        std::cout << "Copy assignment operator called.\n";

        std::cout << "Canonical form test completed without errors.\n";
    }

    return 0;
}
