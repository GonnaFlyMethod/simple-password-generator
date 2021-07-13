#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include "pass_helpers.h"


using namespace PasswordGenerator;


bool PasswordGenerator::is_pass_len_right(std::string user_ans)
{
    // Checks if user's input is right about password length
    // The password length should be integer

    for(unsigned short i=0;i < user_ans.size();++i)
    {
        if(!(isdigit(user_ans[i])))
        {
            return false;
        }
    }
    return true;
}


bool PasswordGenerator::is_binary_user_answer_right(std::string user_ans)
{
    // Checks if user's input in the question with 2 possible answers is right

    if (user_ans == "y" || user_ans == "n" || user_ans == "Y" || user_ans == "N")
        return true;

    return false;
}


PasswordInfo PasswordGenerator::fill_struct_for_password_generation(PasswordInfo password_info)
{
    // Jump to the point below if user's parameters for the password generation are not right
    password_creation_entry_point:
        password_info.pass_len = 0;
        password_info.include_digits = false;
        password_info.include_ascii_letters_uppercase = false;
        password_info.include_ascii_letter_lowercase = false;
        password_info.pass_elements_num = 0;

        bool is_len_right = false;
        std::string user_ans;
        while (!(is_len_right))
        {
            std::cout << "Password length: ";

            std::cin >> user_ans;

            if (!(is_pass_len_right(user_ans)))
                continue;
            else
                password_info.pass_len = std::stoi(user_ans);

            if (!(password_info.pass_len))
            {
                std::cout << "[ERROR] The length of your password can't be 0" << std::endl;
                continue;
            }
            else if (password_info.pass_len < 0)
            {
                std::cout << "The length of your password can't be negative" << std::endl;
            }
            else if (password_info.pass_len < 4)
            {
                std::cout << "[ERROR] Your password is too short" << std::endl;
            }
            else
            {
                is_len_right = true;
            }
        }

        std::cout << "[OK]" << std::endl;

        std::string user_ans_include_digits;
        bool is_input_right;

        do
        {
            std::cout << "Should your password include digits? [y/n] ";
            std::cin >> user_ans_include_digits;

            is_input_right = is_binary_user_answer_right(user_ans_include_digits);
        }while(!(is_input_right));

        if (user_ans_include_digits == "y" || user_ans_include_digits == "Y")
        {
            password_info.include_digits = true;
            password_info.pass_elements_num++;
        }
        else
        {
            password_info.include_digits = false;
        }
        std::cout << "[OK]" << std::endl;
        std::string include_ascii_letters_user_answer;

        do
        {
            std::cout << "Should your password include ascii letters? [y/n] ";
            std::cin >> include_ascii_letters_user_answer;

            is_input_right = is_binary_user_answer_right(include_ascii_letters_user_answer);
        }while(!(is_input_right));

        bool include_ascii_letters;
        if (include_ascii_letters_user_answer == "y" || include_ascii_letters_user_answer == "Y")
        {
            include_ascii_letters = true;
            bool is_option_setted = false;
            do
            {

                if (include_ascii_letters)
                {
                    std::string user_answer;
                    std::cout << "Please, choose one option:" << std::endl;
                    std::cout << "1) ascii uppercase and lowercase" << std::endl;
                    std::cout << "2) ascii uppercase only" << std::endl;
                    std::cout << "3) ascii lowercase only" << std::endl;
                    std::cout << "[1/2/3]" << std::endl;

                    std::cin >> user_answer;

                    if (user_answer == "1")
                    {
                        password_info.include_ascii_letters_uppercase = true;
                        password_info.include_ascii_letter_lowercase = true;
                        password_info.pass_elements_num += 2;
                        is_option_setted = true;
                    }
                    else if (user_answer == "2")
                    {
                        password_info.include_ascii_letters_uppercase = true;
                        password_info.include_ascii_letter_lowercase = false;
                        password_info.pass_elements_num++;
                        is_option_setted = true;
                    }
                    else if (user_answer == "3")
                    {
                        password_info.include_ascii_letters_uppercase = false;
                        password_info.include_ascii_letter_lowercase = true;
                        password_info.pass_elements_num++;
                        is_option_setted = true;
                    }

                }

            } while(!(is_option_setted ));
        }
        else
        {
            include_ascii_letters = false;
        }

    std::cout << "[OK]" << std::endl;
    std::string include_special_symbols_user_answer;

    do
    {
        std::cout << "Should your password include special symbols? [y/n] ";
        std::cin >> include_special_symbols_user_answer;

        is_input_right = is_binary_user_answer_right(include_special_symbols_user_answer);
    }while(!(is_input_right));


    if (include_special_symbols_user_answer == "y" || include_special_symbols_user_answer == "Y")
    {
        password_info.include_special_characters = true;
        password_info.pass_elements_num++;
    }
    else
    {
        password_info.include_special_characters = false;
    }

    if ((!password_info.pass_elements_num))
    {
        char user_try_again_answer;
        std::cout << "Password can not be created with such parameters. Try again ? [y/n] ";

        std::cin >> user_try_again_answer;
        if (user_try_again_answer == 'y')
        {
            std::cout << std::endl;
            goto password_creation_entry_point;
        }

    }
    else
    {
        std::cout << "[OK]" << std::endl;
    }
    return password_info;

}


std::string PasswordGenerator::generate_password(PasswordInfo password_info)
{
    const char digits[10] = {'0', '1', '2', '3', '4', '5' ,'6' , '7', '8', '9'};
    const char ascii_upper_case[26] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
        'P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    const char ascii_lower_case[26] = {
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
        'p','q','r','s','t','u','v','w','x','y','z'
    };
    const char special_symbols[33] = {' ', '!', '"', '#', '$', '%', '&', '\'', '(', ')', '*', '+', ',',
                                     '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']',
                                     '^', '_', '`', '{', '|', '}', '~'};

    std::string password_no_shuffle = "";

    // Initial password generation without shuffling
    while (password_no_shuffle.size() < password_info.pass_len)
    {
        if (password_info.include_digits && password_no_shuffle.size() < password_info.pass_len)
        {
            int arr_digits_size = sizeof(digits) / sizeof(digits[0]);
            int rand_index = rand() % arr_digits_size;
            int pass_el = digits[rand_index];
            password_no_shuffle += pass_el;
        }

        if (password_info.include_ascii_letters_uppercase && password_no_shuffle.size() < password_info.pass_len)
        {
            int arr_upper_size = sizeof(ascii_upper_case) / sizeof(ascii_upper_case[0]);
            int rand_index = rand() % arr_upper_size;
            char pass_el = ascii_upper_case[rand_index];
            password_no_shuffle += pass_el;
        }

        if (password_info.include_ascii_letter_lowercase && password_no_shuffle.size() < password_info.pass_len)
        {
            int arr_lower_size = sizeof(ascii_lower_case) / sizeof(ascii_lower_case[0]);
            int rand_index = rand() % arr_lower_size;
            char pass_el = ascii_lower_case[rand_index];
            password_no_shuffle += pass_el;
        }

        if (password_info.include_special_characters && password_no_shuffle.size() < password_info.pass_len)
        {
            int arr_special_s_size = sizeof(special_symbols) / sizeof(special_symbols[0]);
            int rand_index = rand() % arr_special_s_size;
            char pass_el = special_symbols[rand_index];
            password_no_shuffle += pass_el;
        }
    }

    // Shuffle password
    std::random_shuffle(password_no_shuffle.begin(), password_no_shuffle.end());
    return password_no_shuffle;
}
