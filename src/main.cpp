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

int main(){
    ifstream file("src/DecVlSu.json");
    if(!file.is_open()){
        cout<<"Ошибка открытия файла! ";
        return 1;
    }
    
    string jsonContent((istreambuf_iterator<char>(file)),istreambuf_iterator<char>());
    file.close();
    
    Document doc;
    if(doc.Parse(jsonContent.c_str()).HasParseError()){
        cerr<<"Ошибка парсинга JSON "<<endl;
        return 1;
    }
    if(!doc.IsObject()){
        cerr<<"Некоректный формат JSON"<<endl;
        return 1; 
    }

    cout <<"+"<<string(12, '-')<<"+"<<string(14,'-')<<"+"<<string(12, '-')<<"+"<<endl;
    cout << left << setw(20) << "Предмет"
         << setw(30) << "Название теста"
         << setw(15) << "Статус" << endl;
    cout <<"+"<<string(12, '-')<<"+"<<string(14,'-')<<"+"<<string(12, '-')<<"+"<<endl;
    for (auto& subject : doc.GetObject()) {
        string subjectName = subject.name.GetString();

        // Проверяем, есть ли тесты
        if (!subject.value.HasMember("tests") || !subject.value["tests"].IsArray()) {
            cerr << "Ошибка: У предмета нет тестов или формат неверен!" << endl;
            continue;
        }

        bool firstRow = true; // Флаг для печати предмета только на первой строке
        cout << string(65, '-') << endl;

        for (auto& test : subject.value["tests"].GetArray()) {
            string testName = test["name"].GetString();
            string status = test["completed"].GetBool() ? "Выполнен" : "Не выполнен";

            cout << subjectName << setw(12) << left << testName
                << setw(8) << status << endl;

        }
    }
    
    return 0;
}