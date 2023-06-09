#include <iostream>
using namespace std;

struct Task
{
    char* name{};
    char* priority{};
    char* descr{};
    char* data{};
    char* dataEnd{};

    void taskInfo()
    {
//        cout << "Name" << '\t' << "Priority" << '\t' << "Desciption" << '\t' << "Data" << endl;
//        cout << name << '\t' << priority << '\t' << descr << '\t' << data << endl;
        cout << "Name: " << name << endl;
        cout << "Priority: " << priority << endl;
        cout << "Description: " << descr << endl;
        cout << "Data: " << data << endl;
        cout << "Data end: " << dataEnd << endl;

    }
    char* charToString()
    {
        char *str = new char[1500]{};
        sprintf_s(str, 1500, "%s\n%s\n%s\n%s\n%s\n", name, priority, descr, data, dataEnd);

        return str;
    }

};

Task* createTask()
{
    Task* tasks = new Task{};

    tasks->name = new char[100]{};
    tasks->descr = new char[100]{};
    tasks->priority = new char[100]{};
    tasks->data = new char[100]{};
    tasks->dataEnd = new char[100]{};

    int choiceData = 0;
    char* dayChoice = new char[]{"Day"};
    char* weekChoice = new char[]{"Week"};
    char* monthChoice = new char[]{"Month"};

    cout << "Enter task name: ";
    cin.getline(tasks->name, 101);

    cout << "Enter task description: ";
    cin.getline(tasks->descr,101);

    cout << "Enter task priority: ";
    cin.getline(tasks->priority, 101);

    cout << "Enter task data (to do): ";
    cin.getline(tasks->data, 101);

    cout << "Task data end \n1.Day\n2.Week\n3.Month" << endl;
    cin >> choiceData;

    switch (choiceData) {
        case 1:
        {
            for (int i = 0; i < 100; ++i) {
                tasks->dataEnd[i] = dayChoice[i];
            }
            break;
        }
        case 2:
        {
            for (int i = 0; i < 100; ++i) {
                tasks->dataEnd[i] = weekChoice[i];
            }
            break;
        }
        case 3:
        {
            for (int i = 0; i < 100; ++i) {
                tasks->dataEnd[i] = monthChoice[i];
            }
            break;
        }
    }




    return tasks;
}

void saveToFile(Task* task)
{
    FILE *file{};
    fopen_s(&file,"case.txt", "a+");
    if (file == nullptr)
        return;
    fprintf(file,"%s", task->charToString());
    fclose(file);
}


int main()
{
    int count = 0;
    Task** tasks = new Task*[count]{};
    int indexAddArr = 0;
    int choice = 0;
    int deleteChoice = 0;
    int changeTask = 0;
    do {
        choice = 0;
        cout << "1. Add task" << endl;
        cout << "2. Show tasks" << endl;
        cout << "3. Delete task" << endl;
        cout << "4. Change task" << endl;
        cout << "5. Task name for search" << endl;
        cout << "6. Task priority for search" << endl;
        cout << "7. Task description for search" << endl;
        cout << "8. Task data for search" << endl;
        cout << "9. Show task list on day" << endl;
        cout << "10. Show task list on week" << endl;
        cout << "11. Show task list on month" << endl;
        cout << "14. Stop" << endl;
        cin >> choice;

        if (choice <= 0 || choice > 14)
        {
            cout << "Please numbers! Restart program and try again with numbers!";
            break;
        }

        switch (choice) {
            case 1:
            {
                cin.ignore();
                tasks[indexAddArr] = createTask();
                count++;
                saveToFile(tasks[indexAddArr]);
                indexAddArr++;
                break;
            }
            case 2:
            {
                for (int i = 0; i < indexAddArr; i++) {
                    tasks[i]->taskInfo();
                    cout << endl;
                }
                break;
            }
            case 3:
            {
                cout << "Enter task number for delete: ";
                cin >> deleteChoice;
                if (deleteChoice <= 0 || deleteChoice > indexAddArr+1)
                {
                    cout << "Please numbers! Restart program and try again with numbers!";
                    break;
                }

                for (int i = deleteChoice-1; i < count-1; ++i) {
                    tasks[i] = tasks[i+1];
                }
                indexAddArr--;
                count--;

                FILE *file{};
                fopen_s(&file,"case.txt", "w");

                if (file == nullptr)
                    break;

                fprintf(file,"%s", tasks[deleteChoice-1]->charToString());
                fclose(file);

                break;
            }
            case 4:
            {
                cout << "Enter number task for change its: ";
                cin >> changeTask;
                if (changeTask <= 0 || changeTask > indexAddArr+1)
                {
                    cout << "Please numbers! Restart program and try again with numbers!";
                    break;
                }

                char* newName = new char[100]{};
                char* newPriority = new char[100]{};
                char* newDesc = new char[100]{};
                char* newData = new char[100]{};

                getchar();
                cout << "Enter new name: ";
                cin.getline(newName,100);

                cout << "Enter new priority: ";
                cin.getline(newPriority, 100);

                cout << "Enter new description: ";
                cin.getline(newDesc, 100);

                cout << "Enter new data: ";
                cin.getline(newData, 100);

                tasks[changeTask-1]->name = newName;
                tasks[changeTask-1]->priority = newPriority;
                tasks[changeTask-1]->descr = newDesc;
                tasks[changeTask-1]->data = newData;

                for (int i = 0; i < indexAddArr; ++i) {
                    tasks[i]->taskInfo();
                    cout << endl;
                }

                FILE *file{};
                fopen_s(&file,"case.txt", "w");

                if (file == nullptr)
                    break;

                fprintf(file,"%s", tasks[changeTask-1]->charToString());
                fclose(file);
                changeTask = 0;

                break;
            }
            case 5:
            {
                char* nameSearch = new char[100]{};

                cout << "Enter task name for search: ";
                cin.ignore();
                cin.getline(nameSearch, 100);

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while (tasks[i]->name[j] != '\0' && nameSearch[j] != '\0') {
                        if (tasks[i]->name[j] != nameSearch[j])
                            break;
                        j++;
                    }

                    if (tasks[i]->name[j] == '\0' && nameSearch[j] == '\0')
                    {
                        tasks[i]->taskInfo();
                        cout << endl;
                    }
                }

                delete[] nameSearch;
                break;
            }
            case 6:
            {
                char* prioritySearch = new char[100]{};

                cout << "Enter task priority for search: ";
                getchar();
                cin.getline(prioritySearch, 100);

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while(tasks[i]->priority[j] != '\0' && prioritySearch[j] != '\0')
                    {
                        if (tasks[i]->priority[j] != prioritySearch[j])
                            break;
                        j++;

                        if (tasks[i]->priority[j] == '\0' && prioritySearch[j] == '\0')
                        {
                            tasks[i]->taskInfo();
                            cout << endl;
                        }
                    }
                }
                delete[] prioritySearch;
                break;
            }
            case 7:
            {
                char* descrSearch = new char[100]{};

                cout << "Enter task description for search: ";
                getchar();
                cin.getline(descrSearch, 20);

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while(tasks[i]->descr[j] != '\0' && descrSearch[j] != '\0')
                    {
                        if(tasks[i]->descr[j] != descrSearch[j])
                            break;
                        j++;
                    }

                    if (tasks[i]->descr[j] == '\0' &&  descrSearch[j] == '\0')
                    {
                        tasks[i]->taskInfo();
                        cout << endl;
                    }
                }

                delete[] descrSearch;
                break;
            }
            case 8:
            {
                char* dataSearch = new char[100]{};

                cout << "Enter task data for search: ";
                getchar();
                cin.getline(dataSearch,20);

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while (tasks[i]->data[j] != '\0' && dataSearch[j] != '\0')
                    {
                        if(tasks[i]->data[j] != dataSearch[j])
                            break;
                        j++;
                    }
                    if (tasks[i]->data[j] == '\0' && dataSearch[j] == '\0')
                    {
                        tasks[i]->taskInfo();
                        cout << endl;
                    }
                }

                delete[] dataSearch;
                break;
            }
            case 9:
            {
                char* day = new char[]{"Day"};

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while(tasks[i]->dataEnd[j] != '\0' && day[j] != '\0')
                    {
                        if (tasks[i]->dataEnd[j] != day[j])
                            break;
                        j++;
                    }
                    if (tasks[i]->dataEnd[j] == '\0' && day[j] == '\0')
                    {
                        tasks[i]->taskInfo();
                        cout << endl;
                    }
                }
                delete[] day;
                break;
            }
            case 10:
            {
                char* week = new char[]{"Week"};

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while(tasks[i]->dataEnd[j] != '\0' && week[j] != '\0')
                    {
                        if (tasks[i]->dataEnd[j] != week[j])
                            break;
                        j++;
                    }
                    if (tasks[i]->dataEnd[j] == '\0' && week[j] == '\0')
                    {
                        tasks[i]->taskInfo();
                        cout << endl;
                    }
                }
                delete[] week;
                break;
            }
            case 11:
            {
                char* month = new char[]{"Month"};

                for (int i = 0; i < indexAddArr; ++i) {
                    int j = 0;
                    while(tasks[i]->dataEnd[j] != '\0' && month[j] != '\0')
                    {
                        if (tasks[i]->dataEnd[j] != month[j])
                            break;
                        j++;
                    }
                    if (tasks[i]->dataEnd[j] == '\0' && month[j] == '\0')
                    {
                        tasks[i]->taskInfo();
                        cout << endl;
                    }
                }

                delete[] month;
                break;
            }
        }
    }while(choice != 14);


    delete[] tasks;

    return 0;
}


