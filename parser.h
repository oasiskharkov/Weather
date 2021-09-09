#pragma once

#include <iostream>
#include <fstream>

#include "currency.h"
#include "weather.h"

class Parser
{
public:
   Parser(const std::wstring& fileName);
   ~Parser();
   Parser(const Parser&) = delete;
   Parser& operator = (const Parser&) = delete;
   
   void parse();
   void print() const;
private:
   std::wifstream m_input;
   Weather m_weather;
   Currency m_usd;
   Currency m_eur;
};