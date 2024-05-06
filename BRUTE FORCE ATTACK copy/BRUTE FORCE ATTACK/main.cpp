#include <iostream>
#include <string>
#include <vector>

// This function attempts to find the given password by recursively generating every possible combination of characters
// up to the length of the provided password.
void generateAndCheck(const std::string& password, std::string& currentGuess, int index, const std::string& characters, int& attempts, bool& found) {
    // If the password has already been found, we use this check to exit the recursion early,
    // preventing unnecessary processing.
    if (found) return;

    // Check if we have built a guess that is as long as the original password.
    if (index == password.length()) {
        // Increase the attempt count each time a new combination of the password's length is generated.
        attempts++;
        std::cout<<currentGuess<<std::endl;
        // Compare the current generated combination to the actual password.
        if (currentGuess == password) {
            // If the guess is correct, print the result and mark the search as completed by setting 'found' to true.
            std::cout << "Password found: " << currentGuess << std::endl;
            std::cout << "Total attempts: " << attempts << std::endl;
            found = true;
        }
        return; // Return to stop further processing at this recursion level. for (char c : characters) doesnot run anymore
    }

    // Iterate over each character in the available character set to build the next character of the current guess.
    for (char c : characters) {
        // Set the character at the current index in the guess.
        currentGuess[index] = c;
        // Recursively call the function to set the next character.
        generateAndCheck(password, currentGuess, index + 1, characters, attempts, found);
    }
}

int main() {
    std::string password;
    // Prompt the first player to enter a password.
    std::cout << "Player 1, please enter your password: ";
    std::cin >> password;

    // Define the set of characters that can be used in the password. This includes uppercase and lowercase letters,
    // digits, and a set of special characters.
    const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%";

    // Initialize variables to count the number of password guess attempts and to check if the password has been found.
    int attempts = 0;
    bool found = false;
    
    // Start with the first character of 'characters' for each character of the password length to initialize guesses.
    std::string currentGuess(password.length(), characters[0]);

    // Call the function that starts the recursive password generation and checking process.
    generateAndCheck(password, currentGuess, 0, characters, attempts, found);

    // If the password was not found after all possible combinations, inform the user.
    if (!found) {
        std::cout << "Password not found after " << attempts << " attempt." << std::endl;
    }

    return 0;
}
