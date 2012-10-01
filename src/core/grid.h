#include <vector>

using namespace std;

class Grid
{
protected:
    int n, m;
    vector<int> gift;

public:
    vector<vector<int> > matrix;

    Grid( const int n, const int m );
    int operator()( const int x, const int y);
    bool is_cell_free( const int x, const int y );
    void spawn_bonuses();
    void set(int x, int y, int n);    
    void spawn_player( const int cell_free );
    void print_matrix();
};
