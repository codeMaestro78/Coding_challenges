#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <cstddef>
#include <unistd.h>

struct Flags {
    bool c = false;
    bool l = false;
    bool w = false;
    bool m = false;
};


// Counting UTF-8 Characters

size_t count_utf8_chars(const std::vector<char>& buffer){
    size_t count = 0;
    for(unsigned char c: buffer){
        // here we are counting the bytes which arent continuation bytes
        if((c & 0xC0)!= 0x80){
            count++;
        }
    }
    return count;

}

// Counting words

size_t count_words(const std::vector<char>& buffer){
    size_t words = 0;
    bool in_word = false;
    for(char c : buffer){
        if(std::isspace(static_cast<unsigned char>(c))){
            in_word = false;
        }else if(!in_word){
            in_word = true;
            words++;
        }
    }
    return words;
}

// processing and output formatting

void process_stream(const std::vector<char>& buffer, Flags flags, const std::string& label){
    if(!flags.c && !flags.l && !flags.w && !flags.m){
        flags.c=flags.l=flags.w=flags.m = true;
    }

    size_t num_bytes = buffer.size();

    size_t num_lines =0;

    for (char c :buffer){
        if(c == '\n'){
            num_lines++;
        }
    }

    size_t  num_words = count_words(buffer);
    size_t num_chars = count_utf8_chars(buffer);

    std::ostringstream output;

    if(flags.l) output << std::setw(8) << num_lines;
    if(flags.w) output << std::setw(8) << num_words;
    if(flags.c) output << std::setw(8) << num_bytes;
    if(flags.m) output << std::setw(8) <<  num_chars;


    if(!label.empty()){
        output << " " << label;
    }

    std::cout << output.str() << std::endl;
}

// Parsing arguments & standard entrypoint

int main(int argc, char* argv[] ){
    Flags flags;
    int opt;

    // command line flag parsin loop

    while((opt = getopt(argc,argv ,"clwm"))!= -1) {
        switch(opt) {
            case 'c' : flags.c = true; break;
            case 'l' : flags.l = true; break;
            case 'w' : flags.w = true; break;
            case 'm' : flags.m = true; break;
            default:
                return 1;
        }
        }

        std::vector<char> buffer;
        std::string label;


        if(optind >= argc){
            char c;
            while(std::cin.get(c)){
                buffer.push_back(c);
            }
        }
        else{
            label = argv[optind];
            std::ifstream file(label, std::ios::binary);
            if(!file){
                std::cerr << "ccwc: " << label << ": No such file or directory\n";
            return 1;
            }

            // idiomatic cpp trick : load the entire file into the vector once

            buffer = std::vector<char>((
                std::istreambuf_iterator<char>(file)
            ), std::istreambuf_iterator<char>());
        }

        process_stream(buffer, flags, label);
        return 0;
}
