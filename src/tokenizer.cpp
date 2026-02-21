#include "tokenizer.h"
#include <algorithm>
#include <cctype>
#include <sstream>

std::vector<std::string> Tokenizer::tokenize(const std::string& text) {
    std::vector<std::string> tokens;
    std::string processed;

    // convecrt to lowercase + replace non alphabetic by space
    // clean characters
    for(char c : text){
        if(std::isalpha(c)) {
            processed += std::tolower(c);
        }
        else {
            processed += ' ';
        }
    }

    // split by whitespace
    std::istringstream iss(processed);
    std::string token;
    while(iss >> token){ // Multiple spaces collapse into one during extraction
        if(!token.empty()){
            tokens.push_back(token);
        }
    }

    return tokens;
}




// auto words = Tokenizer::tokenize("Hello, World! 123");
// for (const auto& w : words) {
//     std::cout << w << std::endl;  // Prints: hello\nworld
// }
