#include <iostream>
#include <time.h>
#include <vector>
#include <queue>
#define M 9
#define MINE_NUM 10
using namespace std;

struct coordinate
{
    int row, col;
};
typedef struct coordinate COOR;

unsigned int nums_boom_left = 10;
vector<vector<int>> mine_field; //Mang chua bai min va cac thong so
vector<vector<char>> rt_map; //Mang thoi gian thuc cua nguoi choi
vector<vector<bool>> check_map; //Mang chua cac o da duoc lat
void play_game();
void rand_mine();
void initial_mine_field();
void print_rt_map();
void update_mine_field();
void go_to_coordinate();
void set_flag();
void print_mine_field();
bool has_hit_boom = false;
char int_to_char(int);


char int_to_char(int x)
{
    if (x == 9)
        return '9';
    if (x == 8)
        return '8';
    if (x == 7)
        return '7';
    if (x == 6)
        return '6';
    if (x == 5)
        return '5';
    if (x == 4)
        return '4';
    if (x == 3)
        return '3';
    if (x == 2)
        return '2';
    if (x == 1)
        return '1';
}
bool finish_game()
{
    return (has_hit_boom == true || nums_boom_left == 0);
}
void update_mine_field()
{
    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            if (mine_field[i][j] == 9)
                continue;
            else
            {
                int dem = 0;
                for (int u = i - 1; u <= i + 1; ++u)
                {
                    for (int v = j - 1; v <= j + 1; ++v)
                    {
                        if (u < 0 || u >= M || v < 0 || v >= M)
                            continue;
                        if (u == i && v == j)
                            continue;
                        if (mine_field[u][v] == 9)
                            dem++;
                    }
                }
                mine_field[i][j] = dem;
            }
        }
    }
}
void print_mine_field()
{
    cout << "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
    for (int i = 0; i < M; ++i)
    {
        cout << "----------------------------------------" << endl;
        cout << " " << i + 1 << "|";
        for (int j = 0; j < M; ++j)
            cout << " " << mine_field[i][j] << " |";
        cout << endl;
    }
    cout << endl;
}
void print_rt_map()
{
    cout << "  | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |" << endl;
    for (int i = 0; i < M; ++i)
    {
        cout << "----------------------------------------" << endl;
        cout << " " << i + 1 << "|";
        for (int j = 0; j < M; ++j)
            cout << " " << rt_map[i][j] << " |";
        cout << endl;
    }
    cout << endl;
}

void initial_mine_field()
{
    //Khoi tao 3 mang
    //+ mine_field = {0} -> khong chua bom
    //+ rt_map = 'x' -> an tat ca du lieu
    //+ check_map = {false} -> tat ca o deu chua duoc mo
    mine_field.resize(M);
    rt_map.resize(M);
    check_map.resize(M);
    for (int i = 0; i < M; ++i)
    {
        mine_field[i].resize(M);
        rt_map[i].resize(M);
        check_map[i].resize(M);
        for (int j = 0; j < M; ++j)
        {
            mine_field[i][j] = 0;
            rt_map[i][j] = 'x';
            check_map[i][j] = false;
        }
    }
    //Tao random min
    rand_mine();
    //Update cac o ben canh min
    update_mine_field();
}

void rand_mine()
{
    //Tao random min vao mang mine_field
    //Neu da ton tai min tai vi tri thi giam bien dem de thuc hien random lai
    //Neu chua ton tai thi set mine_field[x][y] = 9 tuc co min.
    srand(time(NULL));
    for (int i = 0; i < MINE_NUM; ++i)
    {
        int x = rand() % M;
        int y = rand() % M;
        if (mine_field[x][y] == 9)
            i--;
        else
            mine_field[x][y] = 9;
    }
}
void go_to_coordinate()
{
    cout << "Enter coordinate: ";
    int x, y;
    cin >> x >> y;
    x--; y--;

    if (mine_field[x][y] == 9)
    {
        cout << "Hit boom!!\n";
        has_hit_boom = true;
        return;
    }
    if (check_map[x][y] == true)
    {
        cout << "This coordinate has opened!!<goto>\n";
        return;
    }
    if (mine_field[x][y] != 0 && mine_field[x][y] != 9)
    {
        rt_map[x][y] = int_to_char(mine_field[x][y]);
        check_map[x][y] = true;
        return;
    }
    COOR a;
    a.row = x;
    a.col = y;

    queue<COOR> q;
    q.push(a);
    while (!q.empty())
    {
        a = q.front();
        q.pop();
        for (int u = a.row - 1; u <= a.row + 1; ++u)
        {
            for (int v = a.col - 1; v <= a.col + 1; ++v)
            {
                if (u < 0 || u >= M || v < 0 || v >= M)
                    continue;
                if (u == a.row && v == a.col)
                    continue;
                if (check_map[u][v] == false)
                {
                    if (mine_field[u][v] == 0)
                    {
                        COOR temp;
                        temp.row = u;
                        temp.col = v;
                        q.push(temp);
                        check_map[u][v] = true;
                        rt_map[u][v] = '0';
                    }
                    else
                    {
                        rt_map[u][v] = int_to_char(mine_field[u][v]);
                        check_map[u][v] = true;
                    }
                }

            }
        }
    }

}
void set_flag()
{
    cout << "Enter coordinate: ";
    int x, y;
    cin >> x >> y;
    x--; y--;

    if (check_map[x][y] == true)
    {
        cout << "This coordinate has opened!!<flag>" << endl;
        return;
    }
    if (mine_field[x][y] == 9)
    {
        rt_map[x][y] = '$';
        check_map[x][y] = true;
        nums_boom_left--;
        cout << "Flagged!" << endl;
    }

}

void play_game()
{
    int choose;
    initial_mine_field();
    
    nums_boom_left = 10;
    has_hit_boom = false;
    do
    {
        //cout << "mine_field\n";
        //print_mine_field();
        cout << "rt_map\n";
        print_rt_map();
        cout << "1: coordinate - 2: flag";
        cout << "\nYour choice: ";
        cin >> choose;
        switch (choose)
        {
        case 1:
        {
            go_to_coordinate();
            break;
        }
        case 2:
        {
            set_flag();
            break;
        }
        default:
        {
            cout << "Your input suck!" << endl;
        }
        }
    } while (!finish_game());
    if (has_hit_boom == true)
        cout << "You lose!" << endl;
    else
        cout << "You win!!" << endl;
}
int main()
{
    char c;
    do {
        play_game();
        cout << "Do you want to continue? (y/n): ";
        cin >> c;
    } while (c == 'y');

    return 0;
}
