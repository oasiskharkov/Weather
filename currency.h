#pragma once

class Currency
{
public:
   explicit Currency(std::wstring&& currency = L"") :
      m_currency{std::move(currency)}
   {}
   void setCurrency(const std::wstring& currency);
   std::wstring currency() const;
private:
   std::wstring m_currency;
};

inline void Currency::setCurrency(const std::wstring& currency)
{
   m_currency = currency;
}

inline std::wstring Currency::currency() const
{
   return m_currency;
}

