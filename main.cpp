#include <iostream>
#include "cpr/cpr.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "string"

using namespace nlohmann;
using namespace std;

std::string KEY = "Your api key from https://app.currencyapi.com/";

int months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int main() {
    string vname;
    string vnom;
    string date;
    string file_name;

    cin >> vname >> vnom >> date >> file_name;

    if (date.length() == 10){
        string year;
        string month;
        string day;
        string total_date;
        year = date.substr(6, 4);
        month = date.substr(3, 2);
        day = date.substr(0, 2);
        total_date = year + "-" + month + "-" + day;
        cpr::Response convertRate = cpr::Get(
                cpr::Url{
                        "https://api.currencyapi.com/v3/historical?apikey=" + KEY +"&currencies=RUB&base_currency=" + vname + "&date=" + total_date},
                cpr::Header{{"X-Api-Key", KEY}});
        json curInf = json::parse(convertRate.text);
        double rubValue = curInf["data"]["RUB"]["value"];
        if (file_name != "0"){
            ofstream out;
            out.open(file_name);
            if (out.is_open()){
                out << vname << " " << stod(vnom) << " " << date << " " << rubValue * stod(vnom) << "\n";
            }
            out.close();
            std::cout << "File has been written" << std::endl;
        }
        else{
            cout << vname << " " << stod(vnom) << " " << date << " " << rubValue * stod(vnom) << "\n";
        }
    }
    else{
        string year_1;
        string month_1;
        string day_1;
        string year_2;
        string month_2;
        string day_2;
        string total_date_start;
        string total_date_end;
        year_1 = date.substr(6, 4);
        month_1 = date.substr(3, 2);
        day_1 = date.substr(0, 2);
        year_2 = date.substr(17, 4);
        month_2 = date.substr(14, 2);
        day_2 = date.substr(11, 2);
        string total_date;

        int current_day = stoi(day_1);
        int current_month = stoi(month_1);
        current_day--;
        int module_ = stoi(month_1);
        while(true){
            double rubValue;
            if (current_day == stoi(day_2) && current_month == stoi(month_2)){
                break;
            }
            if(current_day + 1 == months[module_]){
                total_date = year_1 + "-" + to_string(current_month) + "-" + to_string(current_day + 1);
                cpr::Response convertRate = cpr::Get(
                        cpr::Url{
                                "https://api.currencyapi.com/v3/historical?apikey=" + KEY +"&currencies=RUB&base_currency=" + vname + "&date=" + total_date},
                        cpr::Header{{"X-Api-Key", KEY}});
                json curInf = json::parse(convertRate.text);
                rubValue = curInf["data"]["RUB"]["value"];

                current_day = 0;
                current_month++;
                module_ = stoi(month_2);
            }
            else{
                current_day = (current_day + 1) % months[module_];
                total_date = year_1 + "-" + to_string(current_month) + "-" + to_string(current_day);
                cpr::Response convertRate = cpr::Get(
                        cpr::Url{
                                "https://api.currencyapi.com/v3/historical?apikey=" + KEY +"&currencies=RUB&base_currency=" + vname + "&date=" + total_date},
                        cpr::Header{{"X-Api-Key", KEY}});
                json curInf = json::parse(convertRate.text);
                rubValue = curInf["data"]["RUB"]["value"];
            }

            if (file_name != "0"){
                ofstream out;
                out.open(file_name);
                if (out.is_open()){
                    out << vname << " " << stod(vnom) << " " << date << " " << rubValue * stod(vnom) << "\n";
                }
                out.close();
                std::cout << "File has been written" << std::endl;
            }
            else{
                cout << vname << " " << stod(vnom) << " " << date << " " << rubValue * stod(vnom) << "\n";
            }
        }
    }
    return 0;
}
