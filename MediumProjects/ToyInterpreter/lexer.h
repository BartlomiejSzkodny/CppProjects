#ifndef IMPORTER_H
#define IMPORTER_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "token.h"

// Function declaration for lexer
int lexer(const char* filename, std::vector<Token>& tokenBuffer);

#endif // IMPORTER_H