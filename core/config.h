bool configGenerator(std::string path)
{
    debug("Verifying cfg file");
    std::string line, src;
    std::ifstream input_file("config.cfg");
    if (!input_file.is_open())
    {
        std::ofstream output_file("config.cfg");
        output_file << "# " + introHPro + " - Configuration" + "\n\nsrc=\"default\"";
        if (!output_file.is_open())
        {
            errorLog += "Failed to create config file!\n";
            return true;
        }
        output_file.close();
    }
    std::ifstream input("config.cfg");
    while (getline(input, line))
        if (line.find("src=") != std::string::npos)
        {
            src = std::regex_replace(line.substr(line.find("=") + 1), std::regex("\"|\""), "");
            if (src != "default")
                pathToSave = src;
            else 
                pathToSave = "default";
        }
    
    if(pathToSave == "")
    {
        std::cout << "No source path was found in config.cfg!\n";
        return true;
    }
    
    return false;
}