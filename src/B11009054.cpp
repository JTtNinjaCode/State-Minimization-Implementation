#include <iostream>
#include <fstream>
#include "KissFileInfo.h"
#include "DotFileInfo.h"
#include "ReduceState.h"

int main(int argc, char **argv) {
    KissFileInfo kiss_file_info;
    std::ifstream input_kiss_file(argv[1]);
    input_kiss_file >> kiss_file_info;

    DotFileInfo origin_dot_file_info(kiss_file_info);
    std::ofstream output_origin_dot_file(argv[2]);
    output_origin_dot_file << origin_dot_file_info;

    reduceState(kiss_file_info);

    std::ofstream output_kiss_file(argv[3]);
    output_kiss_file << kiss_file_info;

    DotFileInfo minimized_dot_file_info(kiss_file_info);
    std::ofstream output_dot_file(argv[4]);
    output_dot_file << minimized_dot_file_info;
}