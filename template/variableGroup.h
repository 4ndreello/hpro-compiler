struct Group
{
    const std::vector<std::string> components = {"title", "expanded",
                                                 "fullHeight", "horizontalCenter", "id",
                                                 "resize", "size", "titleAlignment",
                                                 "verticalCenter", "visible", "width"};
};

struct Text
{
    const std::vector<std::string> components = {"id","bold", "caption", "datatype", "field",
                                                 "fontSize", "height", "name", "onclick",
                                                 "required", "size", "src", "width", "text"};

};

struct Row
{
    const std::vector<std::string> components = {"button", "checkbox",
                                                 "checkboxlistbox",
                                                 "edit", "file",
                                                 "grid", "gridcolumn",
                                                 "group", "html",
                                                 "image", "listbox",
                                                 "radiobutton", "row",
                                                 "rowseparator", "text",
                                                 "view", "viewfield"};
};