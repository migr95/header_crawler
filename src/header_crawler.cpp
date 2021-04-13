#include <iostream>
#include <getopt.h>
#include <fstream>
#include <vector>
#include <string>
#include <experimental/filesystem>

#include "dot_writer.hpp"

void readfile(std::string file, tree_node* node, std::vector<std::string> dirs)
{
    std::cout << std::endl << "in readfile for " << file << std::endl;
    //std::string dir = file.substr(0, file.rfind("/")+1);

    std::string usedir;
    for (auto& dir : dirs)
    {
        for (const auto & entry : std::experimental::filesystem::directory_iterator(dir))
        {
            std::cout << entry.path().filename().string() << std::endl;
            if (entry.path().filename().string() == file)
            {
                usedir = dir;
            }
        }
    }

    std::ifstream infile(usedir + file);
    std::string line;
    while (std::getline(infile, line))
    {
        if (line.find("#include") == 0)
        {
            if (line.find("\"") != std::string::npos)
            {
                std::string newfile = line.substr(line.find("\"")+1, line.size()-(line.find("\"")+2));
                newfile = newfile.substr(newfile.rfind("/")+1, newfile.size()-(newfile.rfind("/")+1));
                tree_node t_local;
                t_local.key = newfile;
                readfile(newfile, &t_local, dirs);
                node->childs.push_back(t_local);
            }
            else if (line.find("<") != std::string::npos)
            {
                std::string sysfile = line.substr(line.find("<")+1, line.size()-(line.find("<")+2));
                tree_node t_system;
                t_system.key = sysfile;
                node->childs.push_back(t_system);
            }

        }
    }
    std::cout << "finished readfile for " << file << std::endl;
}

int main(int argc, char * argv[])
{
    int c;
    std::vector<std::string> directories;
    std::string mainfile;
    while((c = getopt(argc, argv, "f:d:")) != -1) // note the colon (:) to indicate that 'd' has a parameter and is not a switch
    {
        switch(c)
        {
        case 'f':
        {
            std::string opt = optarg;
            printf("Crawling headers in %s\n", optarg);
            directories.push_back(opt.substr(0, opt.rfind("/")+1));
            mainfile = opt.substr(opt.rfind("/")+1, opt.size()-(opt.rfind("/")+1));
            break;
        }

        case 'd':
        {
            std::cout << "D: " << optarg << std::endl;
            std::string opt = optarg;
            if (opt.find("[") != std::string::npos)
            {
                opt.erase(0, 1);
                //opt.erase(opt.length()-1, 1);
                std::string delimiter = ":";
                size_t pos = 0;
                std::string token;
                while ((pos = opt.find(delimiter)) != std::string::npos) {
                    directories.push_back(opt.substr(0, pos));
                    std::cout << opt.substr(0, pos) << std::endl;
                    opt.erase(0, pos + delimiter.length());
                }
                delimiter = "]";
                pos = opt.find(delimiter);
                directories.push_back(opt.substr(0, pos));
                std::cout << opt.substr(0, pos) << std::endl;
            }
            else
            {
                directories.push_back(opt);
                std::cout << directories[0] << std::endl;
            }
            break;
        }

        default:
        {
            break;
        }
        }
    }

    tree_node t_main;
    t_main.key = mainfile;
    readfile(mainfile, &t_main, directories);

    std::string filename = "headers";
    FILE * dotFile;
    dotFile = fopen ((filename+".dot").c_str() , "w");
    bst_print_dot(&t_main, dotFile);
    fclose (dotFile);

    std::string cmd = "dot -Tps " + filename + ".dot -o " + filename + ".ps";
    system(cmd.c_str());
    cmd = "rm "+filename+".dot";
    system(cmd.c_str()); //remove generatet .dot file

    return 0;
}
