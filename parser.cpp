#include "parser.h"

Parser::Parser(const std::wstring& fileName)
{
   m_input.open(fileName, std::ios::in);
   m_input.imbue(std::locale(".utf8"));
   if (!m_input.is_open())
   {
      throw std::logic_error("Can't open input html file.");
   }
}

Parser::~Parser()
{
   m_input.close();
}

void Parser::parse()
{
   bool weatherFound = false;
   bool usdFound = false;
   bool eurFound = false;
   while (m_input)
   {
      std::wstring wstr;
      std::getline(m_input, wstr);
      if (!weatherFound)
      {
         std::wstring weatherTmpl = L"<div class=\"weather__content\"><a aria-label=\"";
         int pos = wstr.find(weatherTmpl);
         if (pos == std::wstring::npos)
         {
            continue;
         }
         pos += weatherTmpl.length();
         
         std::wstring wfc = wstr.substr(pos, wstr.find('\"', pos) - pos);
         pos = wfc.find(',');
         m_weather.setTemperature(wfc.substr(0, pos));
         m_weather.setFallout(wfc.substr(pos + 2, wfc.length() - (pos + 2)));
         weatherFound = true;
      }
      if (!usdFound)
      {
         std::wstring curTmpl = L"\"inline-stocks__value_inner\">";
         std::wstring usdTmpl = L"USD";
         int pos = wstr.find(usdTmpl);
         pos = wstr.find(curTmpl, pos + usdTmpl.length());
         pos += curTmpl.length();
         m_usd.setCurrency(wstr.substr(pos, wstr.find('<', pos) - pos));
         usdFound = true;
      }
      if (!eurFound)
      {
         std::wstring curTmpl = L"\"inline-stocks__value_inner\">";
         std::wstring eurTmpl = L"EUR";
         int pos = wstr.find(eurTmpl);
         pos = wstr.find(curTmpl, pos + eurTmpl.length());
         pos += curTmpl.length();
         m_eur.setCurrency(wstr.substr(pos, wstr.find('<', pos) - pos));
         eurFound = true;
      }
      
      if (weatherFound and usdFound and eurFound)
      {
         break;
      }
   }
}

void Parser::print() const
{
   std::wcout << L"Прогноз погоды:" << std::endl;
   std::wcout << L"Температура: " << m_weather.temperature() << std::endl;
   std::wcout << L"Осадки: " << m_weather.fallout() << std::endl;
   std::wcout << L"Обмен валют:" << std::endl;
   std::wcout << L"Курс доллара: " << m_usd.currency() << L" руб." << std::endl;
   std::wcout << L"Курс евро: " << m_eur.currency() << L" руб." << std::endl;
}
