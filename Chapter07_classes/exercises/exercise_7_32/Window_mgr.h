#ifndef WINDOW_MGR_H
#define WINDOW_MGR_H
#include <vector>
#include "Screen.h"

class Screen; 


class Window_mgr{

    std::vector<Screen> windows; 

    public:
        using screen_index  = std::vector<Screen>::size_type;

        void clear(screen_index); 


}; 


#endif