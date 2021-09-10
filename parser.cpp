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
         const std::wstring weatherTmpl = L"<div class=\"weather__content\"><a aria-label=\"";
         int pos = wstr.find(weatherTmpl);
         if (pos != std::wstring::npos)
         {
            pos += weatherTmpl.length();
            std::wstring wfc = wstr.substr(pos, wstr.find('\"', pos) - pos);
            pos = wfc.find(',');
            m_weather.setTemperature(wfc.substr(0, pos));
            m_weather.setFallout(wfc.substr(pos + 2, wfc.length() - (pos + 2)));
            weatherFound = true;
         }
      }
      if (!usdFound)
      {
         fillCurrency(wstr, L"USD", usdFound, m_usd);
      }
      if (!eurFound)
      {
         fillCurrency(wstr, L"EUR", eurFound, m_eur);
      }
      
      if (weatherFound and usdFound and eurFound)
      {
         break;
      }
   }
}

void Parser::fillCurrency(const std::wstring& wstr, const std::wstring& pattern, bool& currencyFound, Currency& currency)
{
   const std::wstring curTmpl = L"\"inline-stocks__value_inner\">";
   
   int pos = wstr.find(pattern);
   if (pos != std::wstring::npos)
   {
      pos = wstr.find(curTmpl, pos + pattern.length());
      pos += curTmpl.length();
      currency.setCurrency(wstr.substr(pos, wstr.find('<', pos) - pos));
      currencyFound = true;
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
