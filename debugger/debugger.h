void debug(std::string val)
{
    if (!debugIsOn)
        return;

    if (val.rfind("#") != std::string::npos)
    {
        val.erase(0,1);
        std::cout << val << std::endl;
    }
    else
    {
        debugCall++;
        std::cout << "[DEBUG {" + std::to_string(debugCall) + "}] >> ";
        std::cout << val << " ..." << std::endl;
    }
}