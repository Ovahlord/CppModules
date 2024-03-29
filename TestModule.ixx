export module TestModule; // declares the module

export import <chrono>;
export import <iostream>; // imports and exports the module for other source files that import TestModule

export // exporting multiple functions with a single export keyword
{
    int NumberFive() { return 5; };
    int NumberTen() { return 10; };
}

/*export*/ namespace Logging // you can either export the whole namespace or...
{
    export void MyFunc() // ...only functions which will automatically expose the namespace for them
    {
        std::cout << "My module function just triggered \n";
    }
}
