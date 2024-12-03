#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>

using namespace std;
using namespace rapidjson;

int main()
{
    bool program = true;
    const int subjectWidth = 15; // Ширина колонки для предмета
    const int testWidth = 25;    // Ширина колонки для тестов
    const int statusWidth = 15;  // Ширина колонки для статуса
    while (program)
    {
        cout << "1. Показать таблицу " << endl;
        cout << "2. Изменить " << endl;
        cout << "3. Выход" << endl;
        ifstream file("src/DecVlSu.json");
        if (!file.is_open())
        {
            cout << "Ошибка открытия файла! ";
            return 1;
        }

        string jsonContent((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        Document doc;
        if (doc.Parse(jsonContent.c_str()).HasParseError())
        {
            cerr << "Ошибка парсинга JSON " << endl;
            return 1;
        }
        if (!doc.IsObject())
        {
            cerr << "Некоректный формат JSON" << endl;
            return 1;
        }
        int choise;
        cin >> choise;
        switch (choise)
        {
        case 1:

            // Выводим шапку таблицы
            cout << "+" << string(subjectWidth, '-') << "+"
                 << string(testWidth, '-') << "+"
                 << string(statusWidth, '-') << "+" << endl;
            cout << "|" << setw(subjectWidth) << left << "Предмет"
                 << "|" << setw(testWidth) << left << "Название теста"
                 << "|" << setw(statusWidth) << left << "Статус" << "|" << endl;
            cout << "+" << string(subjectWidth, '-') << "+"
                 << string(testWidth, '-') << "+"
                 << string(statusWidth, '-') << "+" << endl;

            // Обрабатываем JSON и выводим строки
            for (auto &subject : doc.GetObject())
            {
                string subjectName = subject.name.GetString();

                if (!subject.value.HasMember("tests") || !subject.value["tests"].IsArray())
                {
                    cerr << "Ошибка: У предмета нет тестов или формат неверен!" << endl;
                    continue;
                }

                bool firstRow = true; // Флаг для отображения названия предмета только в первой строке
                for (auto &test : subject.value["tests"].GetArray())
                {
                    string testName = test["name"].GetString();
                    string status = test["completed"].GetBool() ? "✅ Выполнен" : "❌ Не выполнен";

                    // Если первая строка, выводим название предмета
                    if (firstRow)
                    {
                        cout << "|" << setw(subjectWidth) << left << subjectName;
                        firstRow = false;
                    }
                    else
                    {
                        cout << "|" << setw(subjectWidth) << left << ""; // Пустая строка для повторяющихся предметов
                    }

                    // Выводим название теста и статус
                    cout << "|" << setw(testWidth) << left << testName
                         << "|" << setw(statusWidth) << left << status << "|" << endl;
                }

                // Горизонтальная линия после каждого предмета
                cout << "+" << string(subjectWidth, '-') << "+"
                     << string(testWidth, '-') << "+"
                     << string(statusWidth, '-') << "+" << endl;
            }
            // if (!subject.value.HasMember("tests") || !subject.value["tests"].IsArray())
            // {
            //     cerr << "Ошибка: У предмета нет тестов или формат неверен!" << endl;
            //     continue;
            // }

            // bool firstRow = true;
            // cout << string(65, '-') << endl;

            // for (auto &test : subject.value["tests"].GetArray())
            // {
            //     string testName = test["name"].GetString();
            //     string status = test["completed"].GetBool() ? "✅Выполнен" : "❌Не выполнен";

            //     cout << subjectName <<" "<< setw(12) << left << testName
            //          << " "<< setw(8) << status << endl;
            // }
            break;
        case 2:
            break;

        case 3:
            program = false;
            break;
        default:
            program = false;
            break;
        }

        return 0;
    }
}