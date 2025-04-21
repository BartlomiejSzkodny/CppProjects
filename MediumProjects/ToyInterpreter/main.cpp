//https://toylang.com/getting_started/quick-start-guide/#/getting_started/
#include "importer.h"

int main(int argc, char const *argv[])
{
    //use the filename from the command line arguments
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    const char* filename = argv[1];
    // Call the lexer function with the filename
    int result = lexer(filename);
    if (result != 0) {
        std::cerr << "Lexer failed with error code: " << result << "\n";
        return result;
    }
    
    return 0;
}
