void gridGenerator(int i)
{
    std::string gridList = "\tgColumn = new hproGridColumn()";
    i += 1;
    for (int c = i; c < arrFile.size(); c++) 
    {
        if(contains(arrFile[c], "gridColumnEnd"))
            break;
    }
}