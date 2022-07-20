std::string rtnType(std::string e, std::string v)
{
    std::string arrOfValues;
    v = v.substr(0, v.size() - 1);

    std::string on_som = (" = \"" + v + "()" + "\""); // For functions()

    std::string typeOne = (" = \"" + v + "\""); // = "X"
    std::string typeTwo = "(\"" + v + "\")";    // ("X")
    std::string typeThree = (" = " + v);        // = X
    std::string typeFour = ("(" + v + ") ");    // (X)

    std::vector<std::string> n = {
        "text", typeTwo, 
        "container", typeOne,
        "fontSize", typeOne,
        "resize", typeThree,
        "title", typeTwo,
        "width", typeOne,
        "value", typeOne,
        "label", typeOne,
        "size", typeOne,
        "datatype", typeOne,
        "name", typeOne,
        "onclick", on_som,
        "checked", typeFour,
        "required", typeThree,
        "disabled", typeThree,
        "field", typeOne,
        "caption", typeTwo,
        "bold", typeThree,
        "expanded", typeThree,
        "height", typeOne,
        "src", typeOne,
        "maxlength", typeThree
    };

    for (int i = 0; i < n.size(); i += 2)
        if (e.find(n[i]) != std::string::npos)
            arrOfValues = n[i + 1];

    if (arrOfValues == "")
    {
        errorLog += e + " is not a valid attribute";
        return "";
    }

    return arrOfValues;
}

bool searchForNum(std::string var)
{
    for (int i = 1; i < 10; i++)
        if (var.find("g" + std::to_string(i)) != std::string::npos)
            return false;
    return true;
}

std::string searchForElement()
{
    std::string html;
    int y;
    bool existRowBegin = false, existRowEnd = false;

    for (int i = 0; i < arrFile.size(); i++)
    {
        y = i;
        bool goodBoolean = true;
        std::string str = get_str_between_two_str(arrFile[i], ".", "");
        str = std::regex_replace(str, std::regex("\\r\\n|\\r|\\n"), "");

        if (contains(str, "rowEnd"))
            existRowEnd = true;

        if (contains(str, "groupEnd"))
        {
            bool goodBoolean = true;
            int z = i;
            std::string id;
            while (goodBoolean)
            {
                z--;
                if (contains(arrFile[z], "Begin"))
                {
                    goodBoolean = false;
                    break;
                }
                if (contains(arrFile[z], "#id"))
                {
                    id = TrimLeft(arrFile[z]);
                    break;
                }
            }
            id = get_str_between_two_str(id, "= ", ";");
            groupElements.push_back(id);
        }

        if (contains(str, "Begin") || existRowEnd)
        {
            if (contains(str, "rowBegin"))
            {
                existRowBegin = true;
                continue;
            }

            if (existRowEnd)
            {
                bool goodBoolean = true;
                int y = i;
                std::string id;
                while (goodBoolean)
                {
                    y--;
                    if (contains(arrFile[y], "rowBegin"))
                    {
                        goodBoolean = false;
                        break;
                    }
                    if (contains(arrFile[y], "#id"))
                    {
                        id = TrimLeft(arrFile[y]);
                        break;
                    }
                }
                if (id == "")
                {
                    errorLog += "Rows cant be empty!";
                    searchBool = true;
                    break;
                }
                id = get_str_between_two_str(id, "= ", ";");
                rowElements.push_back(id);
                existRowEnd = false;
                continue;
            }
            std::string el = eraseSubStr(str, "Begin");
            el[0] = std::toupper(el[0]);

            if (existRowBegin)
            {
                existRowBegin = false;
                elements.push_back("*" + el);
            }
            else
                elements.push_back(el);

            while (goodBoolean)
            {
                y++;
                if (contains(arrFile[y], "End") || contains(arrFile[y], "row"))
                {
                    attributes.push_back("|");
                    goodBoolean = false;
                    break;
                }
                attributes.push_back(arrFile[y]);
            }
        }
    }

    std::string firstG, lastG;
    bool booleanGuy = false;

    if(elements.size() != declaredVars.size())
    {
        errorLog += "Missing some IDs!";
        searchBool = true;
        return "";
    }

    for (int i = 0; i < elements.size(); i++)
    {
        if (!searchForNum(declaredVars[i]))
            firstG = declaredVars[i];

        if (contains(elements[i], "*"))
        {
            elements[i] = eraseSubStr(elements[i], "*");
            html += firstG + ".rowBegin()\n";
        }
        else if (contains(elements[i], "§"))
        {
            elements[i] = eraseSubStr(elements[i], "§");
            booleanGuy = true;
        }
        html += declaredVars[i] + " = new hpro" + elements[i] + "(\"" + declaredVars[i] + "\")" + "\n";
        for (int k = 0; k < attributes.size(); k++)
        {
            num++;
            if (attributes[num] == "|")
                break;
            if (contains(attributes[num], "#id"))
                continue;
            std::string att = get_str_between_two_str(attributes[num], "#", " =");
            std::string val = get_str_between_two_str(attributes[num], "= ", ";");
            std::string var = eraseSubStr(declaredVars[i], "\n");

            if(rtnType(att, val) == "")
            {
                searchBool = true;
                return "";
            }
            html += "\t" + var + "." + att + rtnType(att, val) + "\n";
        }

        if (searchForNum(declaredVars[i]))
            html += "\t" + firstG + ".addElement(" + declaredVars[i] + ")\n";

        for (auto &line : rowElements)
            if (contains(line, declaredVars[i]))
                html += firstG + ".rowEnd()\n";

        for (auto &line : groupElements)
            if (contains(line, declaredVars[i]))
                html += firstG + ".show()\n";
    }
    return html;
}