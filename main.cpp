#define EMPRESA HPro Soluções em TI
#define AUTHOR Gabriel Andreello

#include "header/includes.h"

int main(int argc, char **argv)
{
    if (argc >= 5)
        if (contains(argv[4], "-d"))
            debugIsOn = true;

    debug("#[DEBUG MODE ON - " + introHPro + "]\nDeveloper: Gabriel Andreello\n");

    if (argc <= 3)
    {
        std::cout << introHPro << "\n\nUsage: " << argv[0] << " <file_to_compile> -n <file_name> [-d]" << std::endl;
        return EXIT_FAILURE;
    }

    fileName = argv[3];
    file = argv[1];

    if(configGenerator(argv[0]))
        return EXIT_FAILURE;

    if (!verifyFile(file))
        return EXIT_FAILURE;

    clock_t start = clock();

    if (generateTemplate())
    {
        std::cout << "Successfully generated!" << std::endl;
    }
    else
    {
        std::cout << "Failed to generate template!\nReason(s): " << errorLog << std::endl;
        return EXIT_FAILURE;
    }
    clock_t end = clock();
    // std::cout << "Time elapsed: " << diffclock(end, start) << "ms" << std::endl;

    return EXIT_SUCCESS;
}
