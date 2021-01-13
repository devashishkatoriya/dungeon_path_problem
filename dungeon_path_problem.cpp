#include <iostream>
#include <vector>

using namespace std;

void display_path(const vector<int> path_x, const vector<int> path_y)
{
    cout<<"\nThe completed path is "<<endl;
    for (int i=0; i<path_x.size(); i++)
    {
        cout<<" -> "<<path_x[i]<<","<<path_y[i]<<"\n";
    }
}

bool is_possible(char grid[5][7], const int n, const int m, const int start_x, const int start_y, const int end_x, const int end_y, vector<int> path_x, vector<int> path_y)
{
    if (start_x == end_x && start_y == end_y)
    {
        display_path(path_x, path_y);
        return true;
    }

    const int directions_x[4] = {-1, 0, 1, 0};
    const int directions_y[4] = {0, -1, 0, 1};

    bool result = false;
    for(int i=0; i<4; i++)
    {
        int next_x = start_x + directions_x[i];
        int next_y = start_y + directions_y[i];

        if ((next_x >= 0 && next_x < n) && (next_y >=0 && next_y < m) && (grid[next_x][next_y] != '#'))
        {
            grid[start_x][start_y] = '#';
            path_x.push_back(start_x);
            path_y.push_back(start_y);

            result = result ||is_possible(grid, n, m, next_x, next_y, end_x, end_y, path_x, path_y);

            grid[start_x][start_y] = '.';
            path_x.pop_back();
            path_y.pop_back();
        }
    }

    return result;
}

int main()
{
    cout<<endl;

    const int n = 5, m = 7;
    char grid[n][m] = {
        {'.', '.', '.', '#', '.', '.', '.'},
        {'.', '#', '.', '.', '.', '#', '.'},
        {'.', '#', '.', '.', '.', '.', '.'},
        {'.', '.', '#', '#', '.', '.', '.'},
        {'#', '.', '#', '.', '.', '#', '.'}
    };

    int start_x = 0, start_y = 0;
    int end_x = 4, end_y = 3;

    vector <int> path_x;
    vector <int> path_y;

    bool result = is_possible(grid, n, m, start_x, start_y, end_x, end_y, path_x, path_y);

    cout<<"\nIs the path possible? "<<result<<endl;

    return 0;
}
