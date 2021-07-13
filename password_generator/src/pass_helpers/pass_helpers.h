#pragma once
#include <string>


namespace PasswordGenerator
{
    struct PasswordInfo
    {
        unsigned short pass_len;
        bool include_digits,
             include_ascii_letters_uppercase,
             include_ascii_letter_lowercase,
             include_special_characters;
        int pass_elements_num = 0;
    };

    bool is_pass_len_right(std::string user_ans);
    bool is_binary_user_answer_right(std::string user_ans);
    PasswordInfo fill_struct_for_password_generation(PasswordInfo password_info);
    std::string generate_password(PasswordInfo password_info);
}


