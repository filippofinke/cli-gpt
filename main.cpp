#include <iostream>
#include "openai.hpp"

std::string prompt{
        "Convert this text to a command that works in a Bash shell, answer must output only the command.\nText to convert: "
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <explain your command>" << std::endl;
        return 1;
    }

    std::string description;
    for (int i = 1; i < argc; i++) {
        description.append(argv[i]).append(" ");
    }

    // check if OPENAI_API_KEY is set
    const char *apiKey = std::getenv("OPENAI_API_KEY");
    if (apiKey == nullptr) {
        std::cout << "Please set the OPENAI_API_KEY environment variable" << std::endl;
        return 1;
    }


    openai::start(apiKey);

    openai::Json completion;
    try {
    completion = openai::completion().create({
                                                          {"model", "text-davinci-003"},
                                                          {"prompt", prompt + description},
                                                          {"max_tokens", 100},
                                                          {"temperature", 0}
                                                  });
    } catch (const std::exception &e) {
        std::cout << "Failed to get completion: " << e.what() << std::endl;
        return 1;
    }


    auto command = completion["choices"][0]["text"].get<std::string>();
    command.erase(std::remove(command.begin(), command.end(), '\n'), command.cend());

    std::cout << "Command: " << command << '\n';

    // ask for confirmation
    std::cout << "Execute command? [y/n]: ";
    std::string answer;
    std::cin >> answer;
    if (answer == "y") {
        system(command.c_str());
    }
    return 0;
}
