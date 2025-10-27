import std;
import types;
import compiler;


// xxv grammar
//
// module
//     ::= ( ( declaration | definition ) ';' )*
// declaration
//     ::= function_declaration
//     ::= extern_function_declaration
// function_declaration
//     ::= 'fn' identifier ':' '(' ( identifier ( ',' identifier )* )? ')'
// extern_function_declaration
//     ::= 'extern' function_declaration
// definition
//     ::= function_definition
// function_definition
//     ::= function_declaration '{' ( statement ';' )* '}'
// statement
//     ::= return_statement
// return_statement
//     ::= 'return' number
//
// example
//
// extern
// fn print: (x);
//
// fn main: () {
//     return 0;
// };


auto main() -> i32 {
    std::string program = R"(
        fn main: () {
            return 0;
        };
    )";

    std::println("program: {}", program);

    Compiler compiler;
    
    compiler.exec(std::move(program));

    std::println("Returning 0...");
    return 0;
}
