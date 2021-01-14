#include <iostream>
#include <vector>

using namespace std;

class Path
{
private:
    vector<int> path_x;
    vector<int> path_y;
    int n;
    bool done;

public:
    Path()
    {
        n = 9999;
        done = false;
    }

    void display()
    {
        cout<<"\nThe completed shortest path is "<<endl;
        for (int i=0; i<path_x.size(); i++)
        {
            cout<<" -> "<<path_x[i]<<","<<path_y[i]<<"\n";
        }
    }

    void insert_point(const int x, const int y)
    {
        path_x.push_back(x);
        path_y.push_back(y);
    }

    void pop_point()
    {
        path_x.pop_back();
        path_y.pop_back();
    }

    bool is_done()
    {
        return done;
    }

    void mark_as_done()
    {
        done = true;
        n = path_x.size();
    }

    int get_length()
    {
        return n;
    }
};



Path is_possible(char grid[5][7], const int n, const int m, const int start_x, const int start_y, const int end_x, const int end_y, Path p)
{
    if (start_x == end_x && start_y == end_y)
    {
        p.insert_point(start_x, start_y);
        p.mark_as_done();
        //p.display();
        return p;
    }

    const int directions_x[4] = {-1, 0, 1, 0};
    const int directions_y[4] = {0, -1, 0, 1};

    Path result;
    for(int i=0; i<4; i++)
    {
        int next_x = start_x + directions_x[i];
        int next_y = start_y + directions_y[i];

        if ((next_x >= 0 && next_x < n) && (next_y >=0 && next_y < m) && (grid[next_x][next_y] != '#'))
        {
            grid[start_x][start_y] = '#';
            p.insert_point(start_x, start_y);

            Path curr_result = is_possible(grid, n, m, next_x, next_y, end_x, end_y, p);

            if (curr_result.is_done() && curr_result.get_length() < result.get_length())
            {
                result = curr_result;
            }

            grid[start_x][start_y] = '.';
            p.pop_point();
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

    Path result;

    result = is_possible(grid, n, m, start_x, start_y, end_x, end_y, result);

    cout<<"\nIs the path possible? "<<result.is_done()<<endl;
    if (result.is_done())
    {
        result.display();
        cout<<"\nLength of path: "<<result.get_length()<<endl;
    }

    return 0;
}
