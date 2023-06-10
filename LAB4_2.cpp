#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;
struct Reference { //Структура
     string author;
     string title;
     string year;
     string page;
};
bool isRussian(char ch) { //Функция,проверяет является ли символ русским

    if (ch >= 0 && ch <= 127) {
        return false;
    }
    return true;
}

void printReferences(const  vector<Reference>& references, bool withNumbers) { //Определение функции, которая проверяется, является ли символ русским
    for (size_t i = 0; i < references.size(); i++) {
        if (withNumbers) {
             cout << i + 1 << ". ";
        }
         cout << references[i].author << " " << references[i].year << ". " << references[i].title << " " << references[i].page <<  endl;
    }
}

int main() { //Определение функции, которая является точкой входа в программу
    setlocale(LC_ALL, "RUS");
     vector <Reference> references; //Создание пустого вектора references, который будет хранить ссылки
     ifstream file("baza_dan.txt"); 
    if (!file.is_open()) { // Проверка, удалось ли открыть файл
         cout << "Ошибка открытия файла." <<  endl;
        return 1;
    }

     string line;
    while (getline(file, line)) { //Чтение файла построчно и обработка каждой строки
         string author, title, year, page; //Создание переменных для хранения информации об одной ссылке
         istringstream iss(line); //Создание строкового потока для обработки строки
        getline(iss, author, ','); //Чтение автора из строки
        getline(iss, year, ','); //Чтение года из строки
        getline(iss, title, ','); //Чтение названия из строки
        iss >> page; //Чтение страницы из строки
        Reference ref = { author, title, year, page }; //Создание объекта на основе прочитанных данных
        references.push_back(ref); //Добавление ссылки в вектор
    }
    file.close();


    sort(references.begin(), references.end(), [](const Reference& a, const Reference& b) { //Сортировка ссылок по автору с учетом русских символов

        if (isRussian(a.author[0]) && !isRussian(b.author[0])) { 
            return true;
        }
        else if (!isRussian(a.author[0]) && isRussian(b.author[0])) {
            return false;
        }
        else {
            return a.author < b.author;
        }
        });

     cout << "Список литературы (с номерами):" <<  endl; //Вывод заголовка списка ссылок с номерами на экран
    printReferences(references, true);

     cout <<  endl << "Список литературы (без номеров):" <<  endl;
    printReferences(references, false); //Вывод списка ссылок без номеров на экран

    return 0;
}