struct Position{
    int posX;
    int posY;
};

struct Cell{
    bool wall = false;
    bool visited = false;
    bool trap = false;
    bool mimic = false;
    bool chest = false;
    bool battery = false;
    bool open = false;
};

struct States
{
    bool paused;
    bool won;
    bool lost;
};


struct Inputs{
    int direction;
    bool pause;
    bool select;
};