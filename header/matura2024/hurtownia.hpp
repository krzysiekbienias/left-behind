# pragma once
# include <unordered_map>


struct Hurtownia{
    std::string dataSprzedazy;
    std::string odmiana;
    char poraRoku;
    std::string nip;
    int sprzedazKg;
};


class Sprzedaz{
private:
    std ::vector<Hurtownia> m_hurtownia;
    Hurtownia parseLineToHurtownia(const std::string & line);
public:
    void loadData(std::string fileName); //read txt content and load m_hurtownia
    std::unordered_map<std::string, int> perClient(); //operates on m_hurtownia
    
};

