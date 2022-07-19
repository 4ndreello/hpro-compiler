#pragma once

bool hitTheTop = false;
bool debugIsOn = false;
bool searchBool = false;
int syntaxError = 0;
int num = -1;
int debugCall = 0;
std::string fileName;
std::string errorLog;
std::string file;
std::string pathToSave;
std::string introHPro = "HPro Compiler v0.1";

std::vector<std::string> arrFile;
std::vector<std::string> topImports;
std::vector<std::string> declaredVars;
std::vector<std::string> attributes;
std::vector<std::string> elements;
std::vector<std::string> rowElements;
std::vector<std::string> groupElements;