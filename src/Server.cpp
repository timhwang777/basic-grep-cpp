#include <iostream>
#include <string>
#include <cctype>

bool match_alphanumeric(const std::string& inputs, const std::string& pattern) {
   for(auto input : inputs) {
        if (isalpha(input) || isdigit(input) || input == '_') {
            return true;
        }
   }
   return false;
}

bool match_digits(const std::string& inputs, const std::string& pattern) {
    for (auto input : inputs) {
        if (isdigit(input)) {
            return true;
        }
    }
    return false;
}

bool match_pattern(const std::string& input_line, const std::string& pattern) {
    if (pattern.length() == 1) {
        return input_line.find(pattern) != std::string::npos;
    }
    else if (pattern == "\\d") {
        return match_digits(input_line, pattern);
    }
    else if (pattern == "\\w") {
        return match_alphanumeric(input_line, pattern);
    }
    else {
        throw std::runtime_error("Unhandled pattern " + pattern);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Expected two arguments" << std::endl;
        return 1;
    }

    std::string flag = argv[1];
    std::string pattern = argv[2];

    if (flag != "-E") {
        std::cerr << "Expected first argument to be '-E'" << std::endl;
        return 1;
    }

    std::string input_line;
    std::getline(std::cin, input_line);

    try {
        if (match_pattern(input_line, pattern)) {
            return 0;
        } else {
            return 1;
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
}
