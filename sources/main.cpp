// Copyright 2020 Petr Portnov <gh@progrm-jarvis.ru>

#include <ftp-explorer-lib.hpp>
#include <iostream>

int main(int const argument_count, char* const arguments[]) {
    // alias `filesystem`
    namespace fs = ::ftp_explorer::filesystem;

    fs::path path_to_ftp = argument_count > 2 ? arguments[1] : fs::current_path();
}
