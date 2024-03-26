//
// Created by 张宜鹏 on 2023/2/17.
//

#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <iostream>


std::string src_path = "data";
std::string dst_path = "data_copy";

void copy_file() {
    boost::iostreams::mapped_file_params params_src;
    params_src.path = src_path;
    boost::iostreams::mapped_file_source mf_src;
    mf_src.open(params_src);
    if (mf_src.is_open()) {
        unsigned char *p_src = (unsigned char *) mf_src.data();
        size_t len_src = mf_src.size();

        boost::iostreams::mapped_file_params params_dst;
        params_dst.path = dst_path;
        params_dst.new_file_size = len_src;
        boost::iostreams::mapped_file_sink mf_dst;
        mf_dst.open(params_dst);
        if (mf_dst.is_open()) {
            unsigned char *p_dst = (unsigned char *) mf_dst.data();
            for (size_t i = 0; i < len_src; i++) {
                *(p_dst + i) = *(p_src + i);
            }
            mf_dst.close();
        }
        mf_src.close();
    }
}

using namespace std;
using namespace boost::iostreams;

int print_file_content() {
    //Initialize the memory-mapped file
    mapped_file_source file("data");
    //Read the entire file into a string
    string fileContent(file.data(), file.size());
    //Print the string
    cout << fileContent << endl;
    //Cleanup
    file.close();
}


int main() {
    print_file_content();
    copy_file();

    boost::iostreams::mapped_file_source file;
    file.open("data");

    int size = file.size();
    const char *data = file.data();

    uint64_t f1;
    int32_t f2;
    double f3;

    while (size > 0) {
        f1 = (uint64_t) *data;
        data += sizeof(uint64_t);
        size -= sizeof(uint64_t);
        f2 = (int32_t) *data;
        data += sizeof(int32_t);
        size -= sizeof(int32_t);
        f3 = (double) *data;
        data += sizeof(double);
        size -= sizeof(double);

        std::cout << f1 << ' ' << f2 << ' ' << f3 << '\n';
    }


    return 0;
}