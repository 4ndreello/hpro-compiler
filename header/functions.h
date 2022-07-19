std::string eraseSubStr(std::string &mainStr, const std::string &toErase)
{
    size_t pos = mainStr.find(toErase);
    if (pos != std::string::npos)
    {
        return mainStr.erase(pos, toErase.length());
    }
    return mainStr;
}


bool contains(std::string var, std::string sub)
{
    if (var.find(sub) != std::string::npos)
        return true;
    return false;
}

double diffclock(clock_t clock1, clock_t clock2)
{
    double diffticks = clock1 - clock2;
    double diffms = (diffticks) / (CLOCKS_PER_SEC / 1000);
    return diffms;
}

std::string get_str_between_two_str(const std::string &s, const std::string &start_delim, const std::string &stop_delim)
{
    unsigned first_delim_pos = s.find(start_delim);
    unsigned end_pos_of_first_delim = first_delim_pos + start_delim.length();
    unsigned last_delim_pos = s.find_first_of(stop_delim, end_pos_of_first_delim);
    return s.substr(end_pos_of_first_delim, last_delim_pos - end_pos_of_first_delim);
}

std::string TrimLeft(const std::string &str)
{
    auto pos = str.find_first_not_of(' ');
    return str.substr(pos != std::string::npos ? pos : 0);
}

void getLinesFromFile()
{
    debug("Reading lines");
    std::string line;
    std::ifstream input_file(file);
    while (getline(input_file, line))
    {
        if(TrimLeft(line).rfind("//") != std::string::npos)
            continue;
        arrFile.push_back(line);
    }
    debug("getLinesFromFile() done!");
    input_file.close();
}