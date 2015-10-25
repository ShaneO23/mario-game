#include "dirs.h"

#include <dirent.h>

std::vector<std::string> DirList(const std::string &path) {    
    std::vector<std::string> names;

    DIR *dir;
    struct dirent *ent;
    if((dir = opendir(path.c_str())) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            names.push_back(ent->d_name);
        }
        closedir(dir);
    }

    return names;
}
