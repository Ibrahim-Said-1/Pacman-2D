#include "Map.h"

/**
*   Takes a file and loads in 1s and 0s into different vectors with coordinates
*/
void Map::LoadMap(const char* filepath)
{

    std::ifstream inFile(filepath);

    if (!inFile) {
        std::cout << "Cannot open file.\n";
        return;
    }

    inFile >> width;
    inFile.ignore(1);
    inFile >> height;
    int i = 1, j = 1;
    while (!inFile.eof())
    {
        inFile >> nr;
        //Walls
        if (nr == 1)
        {
            walls.push_back(std::make_pair(i, j));
        }
        //Pellets
        if (nr == 0)
        {
            pellets.push_back(std::make_pair(i, j));
        }
        //Pacman start
        if (nr == 2)
        {
            pacStart.first = i;
            pacStart.second = j;
        }
        //Moves throughout the file with 'j' and 'i'
        i++;
        if (i == 29)
        {
            i = 1;
            j++;
        }
    }

    inFile.close();

}
