#include <iostream>
#include <fstream>
#include <string>
#include <array>

std::string return_command_output(const char* cmd) 
{
    std::array<char, 128> buffer;
    std::string result;

    FILE *terminal_output = popen(cmd, "r"); 

    while (!feof(terminal_output)) 
    {
        if (fgets(buffer.data(), 128, terminal_output) != nullptr)
            result += buffer.data();
    }

    pclose(terminal_output);

    return result;
}

int main()
{
    int succes_count = 0;
    int total_count = 0;

    for (int i = 0; i < 100; i++)
    {
        system("cat include.cpp examples/sm* function.cpp unit-class.cpp > bigOtestFunction.cpp");
        system("g++ -o bigOtestFunction bigOtestFunction.cpp");
        std::string output = return_command_output("./bigOtestFunction");
        if (output.find("SUCCES") != std::string::npos) succes_count++;
        
        total_count++;
    }

    std::cout << "Total succes count: " << succes_count << std::endl;

    std::ofstream file;
    file.open("results.txt", std::ios_base::app);

    file << succes_count << std::endl;

    file.close();
    
    return 0;
}