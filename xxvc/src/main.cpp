import std;

import types;
import compiler;


// example
//
// extern
// print: (x);
//
// main: () {
//     return 0;
// };


auto main() -> i32 {
    std::string program = R"(
        extern
        print: (x);

        main: (x, y) {
            return 21;
        };
    )";

    std::println("program: {}", program);

    Compiler compiler;
    
    compiler.exec(std::move(program));

    std::println("Returning 0...");
    return 0;
}
