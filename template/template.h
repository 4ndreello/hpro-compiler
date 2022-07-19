bool generateTemplate()
{
    debug("Generating template");
    std::string line;
    std::string templateHeader =
        "<!DOCTYPE HTML>\n"
        "<html lang=\"pt-br\">\n"
        "<head>\n"
        "<meta charset=\"utf-8\">\n"
        "<title>HPro Solu&ccedil;&otilde;es de TI</title>\n"
        "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"hpro.css\">\n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"agGrid.css\">\n"
        "<link rel=\"stylesheet\" type=\"text/css\" href=\"agGridTheme.css\">\n"
        "<script src=\"scripts/hproDialog.js\"></script>\n"
        "<script src=\"scripts/hproFunction.js\"></script>\n"
        "<script src=\"scripts/hproMenu.js\"></script>\n"
        "<script src=\"scripts/hproButton.js\"></script>\n"
        "<script src=\"scripts/hproCheckBox.js\"></script>\n"
        "<script src=\"scripts/hproEdit.js\"></script>\n"
        "<script src=\"scripts/hproGrid.js\"></script>\n"
        "<script src=\"scripts/agGrid.js\"></script>\n"
        "<script src=\"scripts/hproGroup.js\"></script>\n"
        "<script src=\"scripts/hproRadioButton.js\"></script>\n"
        "<script src=\"scripts/hproImage.js\"></script>\n"
        "<script src=\"scripts/hproText.js\"></script>\n"
        "<script src=\"scripts/hproChoice.js\"></script>\n"
        "<script src=\"scripts/rotinas.js\"></script>\n"
        "<script src=\"scripts/" +
        fileName + ".js\"></script>\n";

    debug("Opening file");
    getLinesFromFile();

    debug("Checking for primary errors");
    if (checkForErrors())
        return false;

    std::string jsExists(fileName + ".js");
    std::ifstream verifyJS(jsExists);

    if (topImports.size() != 0)
    {
        for (int i = 0; i < topImports.size(); i++)
        {
            topImports[i].erase(topImports[i].size() - 1, '\n');
            topImports[i].erase(0, 1);
            if (topImports[i].find(".js") != std::string::npos)
            {
                templateHeader += "<script src=\"scripts/" + topImports[i] + "\"></script>\n";
            }
            else if (topImports[i].find(".css") != std::string::npos)
            {
                templateHeader += "<link rel=\"stylesheet\" type=\"text/css\" href=\"" + topImports[i] + "\">\n";
            }
        }
    }
    debug("topImports() done!");

    templateHeader += "</head>\n<body style=\"height:100%\"></body>\n";
    templateHeader += "<script>\n";
    for (int i = 0; i < arrFile.size(); i++)
    {
        if (arrFile[i].find("#id") != std::string::npos)
        {
            std::string str = get_str_between_two_str(arrFile[i], "= ", ";");
            str = std::regex_replace(str,
                                     std::regex("\\r\\n|\\r|\\n"),
                                     "");

            for (auto &line : declaredVars)
                if (line == str)
                {
                    errorLog += str + " already declared\n";
                    return false;
                }

            declaredVars.push_back(str);
            templateHeader += "let " + (get_str_between_two_str(arrFile[i], "= ", ";"));
        }
    }

    debug("running searchForElement()");

    templateHeader += "function formCreate() {\n";

    templateHeader += searchForElement();

    debug("done!");

    if (searchBool)
        return false;

    templateHeader += "}\nformCreate()\nformPrepare()\nif(functionExists(\"formLoad\")) eval(\"formLoad()\")\n";
    templateHeader += "</script>\n</html>\n";

    if (!verifyJS)
    {
        std::ofstream jsFile(fileName + ".js");

        jsFile.close();
    }

    std::string file(fileName + ".htm");
    std::ofstream generate(file);
    generate << templateHeader;
    return SUCCESS;
}