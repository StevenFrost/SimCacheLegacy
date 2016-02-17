/**********************************************************************************
*                                                                                *
* Copyright (c) 2016 Steven Frost, Orion Lyau. All rights reserved.              *
*                                                                                *
* This source is subject to the MIT License.                                     *
* See http://opensource.org/licenses/MIT                                         *
*                                                                                *
* THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,    *
* EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED          *
* WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR PURPOSE.         *
*                                                                                *
**********************************************************************************/

#include <Localization/Resolver.h>

#include <assert.h>
#include <cstdint>
#include <Windows.h>

#include "StringResources.h"

namespace SimCache
{
namespace Localization
{

//-----------------------------------------------------------------------------

static std::string g_locale = "en-US";

//-----------------------------------------------------------------------------

std::string WStringToString(wchar_t const* w, size_t size)
{
    if (size == 0)
    {
        return std::string();
    }
    int length = WideCharToMultiByte(CP_UTF8, 0, w, static_cast<int>(size), nullptr, 0, nullptr, nullptr);

    std::string result;
    if (length > 0)
    {
        result.resize(length);
        WideCharToMultiByte(CP_UTF8, 0, w, static_cast<int>(size), &result[0], length, nullptr, nullptr);
    }
    else
    {
        assert(false);
    }
    return result;
}

//-----------------------------------------------------------------------------

std::string WStringToString(std::wstring const& w)
{
    return WStringToString(w.data(), w.length());
}

//-----------------------------------------------------------------------------

std::string GetCurrentLocale()
{
    const uint8_t MAX_STRING_SIZE = 8;
    auto language = GetUserDefaultUILanguage();

    wchar_t langBuffer[MAX_STRING_SIZE] = { 0 };
    DWORD count = GetLocaleInfo(language, LOCALE_SISO639LANGNAME, langBuffer, MAX_STRING_SIZE);
    if (!count)
    {
        throw std::exception("Failed to get language code.");
    }

    wchar_t countryBuffer[MAX_STRING_SIZE] = { 0 };
    count = GetLocaleInfo(language, LOCALE_SISO3166CTRYNAME, countryBuffer, MAX_STRING_SIZE);
    if (!count)
    {
        throw std::exception("Failed to get country code.");
    }

    std::string result = WStringToString(langBuffer);
    result += "-";
    result += WStringToString(countryBuffer);

    return result;
}

//-----------------------------------------------------------------------------

void InitLocale()
{
    try
    {
        g_locale = GetCurrentLocale();
    }
    catch (std::exception const&)
    {
        // We fall back to en-US if there was a problem getting the current locale.
        g_locale = "en-US";
    }
}

//-----------------------------------------------------------------------------

std::string const& GetString(std::string const& id)
{
    return GetString(g_locale, id);
}

//-----------------------------------------------------------------------------

std::string const& GetString(std::string const& locale, std::string const& id)
{
    auto mapIt = STRING_TABLE.find(locale);
    if (mapIt == STRING_TABLE.end())
    {
        // We can guarantuee that en-US will be in the collection, all other
        // locales are translated from it. We can therefore safely fall back to
        // this locale if the user's one isn't present in the collection.
        mapIt = STRING_TABLE.find("en-US");
    }

    // Pull the string table out for the locale.
    auto& strings = (*mapIt).second;

    auto strIt = strings.find(id);
    if (strIt == strings.end())
    {
        throw StringResourceNotFoundException("The requested string resource '" + id + "' could not be found.");
    }

    return (*strIt).second;
}

//-----------------------------------------------------------------------------

} // namespace Localization
} // namespace SimCache
