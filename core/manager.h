bool findAttributes(std::string input, std::vector<std::string> vetor)
{
    for (int i = 0; i < arrFile.size(); i++)
    {
        if (arrFile[i].find(input+"Begin") != std::string::npos)
        {
            int y = i;
            bool boolGuy = true;
            while (boolGuy)
            {
                y++;
                if (arrFile[y].find(input+"End") != std::string::npos)
                {
                    boolGuy = false;
                    break;
                }
                std::string att = get_str_between_two_str(arrFile[y], "#", " =");
                std::string obj;
                for (auto &l : vetor)
                    if (contains(arrFile[y], l))
                        obj = "exists";

                if (obj != "exists")
                {
                    errorLog += att + " is not a valid attribute for " + input;
                    return false;
                }
                    
            }
        }
    }
    return true;
}

bool checkForErrors()
{
    for (int i = 0; i < arrFile.size(); i++)
    {
        if (!hitTheTop)
            if (arrFile[i].find("@") != std::string::npos)
                topImports.push_back(arrFile[i]);

        if (arrFile[i].find("Begin") != std::string::npos)
        {
            hitTheTop = true;
            syntaxError++;
        }
        if (arrFile[i].find("End") != std::string::npos)
            syntaxError--;
    }

    Text text;
    Button button;

    std::vector<std::vector<std::string>> c = {text.components, button.components};
    std::vector<std::string> raw_text = {"text", "button"};

    for(int k = 0; k < c.size(); k++)
        if(findAttributes(raw_text[k], c[k]) == 0)
            return true;

    if (syntaxError != 0)
    {
        errorLog += "Syntax error!\n";
        return true;
    }
    return false;
}

bool verifyFile(std::string fileMain)
{
    debug("Verifying file");
    std::ifstream input_file(fileMain);
    if (!input_file.is_open())
    {
        std::cerr << "Could not open the file - '" << fileMain << "'" << std::endl;
        return FAILURE;
    }

    input_file.close();
    return SUCCESS;
}