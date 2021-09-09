#pragma once

#include <string>

class Weather
{
public:
   explicit Weather(std::wstring&& temperature = L"", std::wstring&& fallout = L"") :
      m_temperature{std::move(temperature)},
      m_fallout{std::move(fallout)}
   {}
   void setTemperature(const std::wstring& temperature);
   std::wstring temperature() const;
   void setFallout(const std::wstring& fallout);
   std::wstring fallout() const;
private:
   std::wstring m_temperature;
   std::wstring m_fallout;
};

inline void Weather::setTemperature(const std::wstring& temperature)
{
   m_temperature = temperature;
}

inline std::wstring Weather::temperature() const
{
   return m_temperature;
}

inline void Weather::setFallout(const std::wstring& fallout)
{
   m_fallout = fallout;
}

inline std::wstring Weather::fallout() const
{
   return m_fallout;
}