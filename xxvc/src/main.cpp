import std;

import types;
import compiler;


auto main(i32 argc, char const* argv[]) -> i32 {
    if (argc == 1) {
        std::println("please specify filename");
        return -1;
    }

    b8 printOpt = false;
    std::string outputFilename = "./a.ll";

    u64 i = 1;
    while (i < argc) {
        std::string_view opt(argv[i]);
        if (!opt.starts_with("--")) break;

        if (opt == "--print") {
            printOpt = true;
        }
        else if (opt == "-o" || opt == "--output") {
            ++i;
            if (i == argc) {
                std::println("please specify output filename");
                return -1;
            }
            outputFilename = argv[i];
        }
        else {
            std::println("unknown option {}", opt);
            return -1;
        }

        ++i;
    }

    if (i == argc) {
        std::println("please specify filename");
        return -1;
    }

    std::string_view filename(argv[i]);

    std::error_code err;
    u64 size = std::filesystem::file_size(filename, err);
    if (err) {
        std::println("couldn't find file {}", filename);
        return -1;
    }
    std::string program(size, '\0');
    std::ifstream file(argv[i]);
    if (file.fail()) {
        std::println("couldn't find file {}", filename);
        return -1;
    }
    file.read(&program[0], size);

    if (printOpt) {
        std::println("{:=<40}", "= program =");
        std::print("{}", program);
    }

    Compiler compiler(printOpt);
    b8 ok = compiler.exec(std::move(program), outputFilename);
    if (!ok) {
        std::println("failed to compile");
        return -1;
    }

    if (printOpt) {
        std::println("{}", std::string(40, '='));
        std::println("returning 0...");
    }

    return 0;
}
