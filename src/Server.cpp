#include <iostream>
#include <string>
#include <cctype>
#include <unordered_set>

bool match_digit(const char c) {
	return std::isdigit(c);
}

bool match_alphanumeric(const char c) {
	return std::isalnum(c);
}

bool match_group(const char c, const std::string& pattern, size_t& pattern_idx) {
	bool negated = pattern[pattern_idx + 1] == '^' ; 
	bool match = false;

	size_t closing_bracket_pos = pattern.find(']', pattern_idx);
	for (int i = pattern_idx + 1 + negated; i < closing_bracket_pos; i++) {
		if (c == pattern[i]) {
			match = true;
			break;
		}
	}
	pattern_idx = closing_bracket_pos;

	return negated ? !match : match;
}

bool matches(char c, const std::string& pattern, size_t& pattern_idx) {
	if (pattern[pattern_idx] == '\\') {
		if (pattern_idx + 1 < pattern.size()) {
			pattern_idx++; // Skip the '\';
			if (pattern[pattern_idx] == 'd') return match_digit(c);
			if (pattern[pattern_idx] == 'w') return match_alphanumeric(c);
		}
	}
	else if (pattern[pattern_idx] == '[') {
		return match_group(c, pattern, pattern_idx);
	}
	else {
		return c == pattern[pattern_idx];
	}

	pattern_idx++; // Move to the next character in the pattern
	return false;
}

bool match_pattern_helper(const std::string& input_line, const std::string& pattern, size_t input_line_idx, size_t pattern_idx) {
	if (input_line_idx == input_line.length() && pattern_idx == pattern.length()) {
		return true; // Both input and pattern are fully matched
	}
	if (pattern_idx == pattern.length()) {
		return false; // Pattern is consumed, but input is not
	}

	if (input_line_idx < input_line.length() && matches(input_line[input_line_idx], pattern, pattern_idx)) {
		return match_pattern_helper(input_line, pattern, input_line_idx + 1, pattern_idx + 1);
	}

	return false;
}

bool match_pattern(const std::string& input_line, const std::string& pattern) {
	return match_pattern_helper(input_line, pattern, 0, 0);
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
