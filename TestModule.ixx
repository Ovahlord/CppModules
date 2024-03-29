export module TestModule; // declares the module
export import <iostream>; // imports and exports the module for other source files that import TestModule

namespace Logging
{
    export void MyFunc()
    {
        std::cout << "My module function just triggered \n";
    }
}
