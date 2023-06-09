#include <iostream>
#include <Windows.h>
using namespace std;
void getClick(int& x, int& y)
{
    HANDLE hConsoleIn = GetStdHandle(STD_INPUT_HANDLE);
    INPUT_RECORD inputRec;
    DWORD events;
    COORD coord;
    bool clicked = false;

    DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    SetConsoleMode(hConsoleIn, fdwMode);

    while (!clicked) {

        ReadConsoleInput(hConsoleIn, &inputRec, 1, &events);

        if (inputRec.EventType == MOUSE_EVENT) {
            if (inputRec.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                coord = inputRec.Event.MouseEvent.dwMousePosition;
                x = coord.X;
                y = coord.Y;
                clicked = true;
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE)) {
            cout << "Exiting" << endl;
            break;
        }
        else if (inputRec.EventType == KEY_EVENT) {
        }
    }
}
void createField(int*& field, int y, int size)
{
    field = new int[size]{};
    int* count = new int[size]{};

    srand(time(NULL));
    int random = 0;
    for (size_t i = 0; i < size - 1; i++)
    {
        random = rand() % (size - 1) + 1;
        if (count[random - 1] < 1)
        {
            field[i] = random;
            count[random - 1]++;
        }
        else
            i--;
    }
}

int main()
{

    int x = 0;
    int y = 0;
    int size = 0;
    int* field = 0;
    cout << "Enter Field size: " << endl;
    cout << "1. 3X3" << endl;
    cout << "2. 4X4" << endl;

    getClick(x, y);

    while (y < 1 && y > 3)
    {
        cout << "Error! Enter again: " << endl;
        getClick(x, y);
    }
    while (y != 1 && y != 2)
        getClick(x, y);
    if (y == 1)
        size = 9;
    else if (y == 2)
        size = 16;

    createField(field, y, size);
    int numbers9[10]{ 80, 160, 240, 81, 161, 241, 82, 162, 242 };
    int numbers16[17]{ 80, 160, 240, 320, 81, 161, 241, 321, 82, 162, 242, 322, 83, 163, 243, 323 };
    int timeFirst = time(NULL);
    int close = 1;
    int move = 0;

    while (close)
    {
        system("cls");
        for (size_t i = 0; i < size; i++)
        {
            cout << '\t';
            if (size == 9)
            {
                cout << field[i] << " ";
                if ((i + 1) % 3 == 0)
                    cout << endl;
            }
            else
            {
                cout << field[i] << " ";
                if ((i + 1) % 4 == 0)
                    cout << endl;
            }
        }
        int trw = 0;
        int choice = 0;
        int i = 0;
        while (trw == 0)
        {
            getClick(x, y);
            int s = 0;
            choice = (x *= 10) + y;
            if (size == 9)
            {
                for (; numbers9[s] != 0; s++)
                {
                    if (choice == numbers9[s])
                    {
                        trw++;
                        i = s;
                        break;
                    }
                }
            }
            else
            {
                for (; numbers16[s] != 0; s++)
                {
                    if (choice == numbers16[s] || choice == numbers16[s] + 10)
                    {
                        trw++;
                        i = s;
                        break;
                    }
                }
            }
        }
        if (size == 9)
        {
            if (field[i + 1] == 0)
            {
                int row = field[i];
                field[i] = field[i + 1];
                field[i + 1] = row;
            }
            else if (field[i - 1] == 0)
            {
                int row = field[i];
                field[i] = field[i - 1];
                field[i - 1] = row;
            }
            else if (field[i + 3] == 0)
            {
                int row = field[i];
                field[i] = field[i + 3];
                field[i + 3] = row;
            }
            else if (field[i - 3] == 0)
            {
                int row = field[i];
                field[i] = field[i - 3];
                field[i - 3] = row;
            }
        }
        else
        {
            if (field[i + 1] == 0)
            {
                int row = field[i];
                field[i] = field[i + 1];
                field[i + 1] = row;
            }
            else if (field[i - 1] == 0)
            {
                int row = field[i];
                field[i] = field[i - 1];
                field[i - 1] = row;
            }
            else if (field[i + 4] == 0)
            {
                int row = field[i];
                field[i] = field[i + 4];
                field[i + 4] = row;
            }
            else if (field[i - 4] == 0)
            {
                int row = field[i];
                field[i] = field[i - 4];
                field[i - 4] = row;
            }
        }
        int stop = 0;
        for (size_t i = 0; i < size - 1; i++)
        {
            if (field[i] == i + 1)
                stop++;
        }
        if (stop == size - 1)
            close = false;
    }

    int timeSec = time(NULL) - timeFirst;
    cout << "You did it in " << timeSec << "seconds!" << endl;
    cout << "for this " << move << " moves";

    return 0;
}