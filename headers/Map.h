#include "Libraries.h"

class Map
{

private:
    int width = 0,
        height = 0,
        nr = 0,
        cnt = 0;
    
public:
    std::vector<std::pair<int, int>> walls;
    std::vector<std::pair<int, int>> pellets;
    std::vector <int> map;
    std::pair<int, int> pacStart;

    void LoadMap(const char* filepath);

};