#include <ctime>
#include <cstdio>
#include <iostream>
#include "pass_helpers/pass_helpers.h"


using namespace PasswordGenerator;


int main()
{
    typedef unsigned int uint;
    srand((uint)time(NULL));

    std::cout << "Welcome to the password generator!\nThere are a number of options that\nshould be setted for your password:"
         << std::endl;

    new_password_generation_full_process:
        PasswordInfo password_info;
        PasswordInfo info_for_password_generation = fill_struct_for_password_generation(password_info);

        if (info_for_password_generation.pass_elements_num > 0)
        {
            std::string password = generate_password(info_for_password_generation);
            std::cout << "Password: " << password << std::endl;

            std::string user_ans;
            bool user_ans_correct;
            do{
                std::cout << "Generate password again ? [y/n] ";
                std::cin >> user_ans;
                user_ans_correct = PasswordGenerator::is_binary_user_answer_right(user_ans);
            }while(!user_ans_correct);

            if (user_ans == "y" || user_ans == "Y" )
            {
                std::cout << std::endl;
                goto new_password_generation_full_process;
            }

        }
    return 0;


}
