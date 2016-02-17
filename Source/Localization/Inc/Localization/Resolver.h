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

#pragma once

#include <exception>
#include <string>

namespace SimCache
{
namespace Localization
{

//-----------------------------------------------------------------------------

struct StringResourceNotFoundException : public std::exception
{
    StringResourceNotFoundException(std::string const& message) :
        std::exception(message.c_str())
    {}
};

//-----------------------------------------------------------------------------

std::string const& GetString(std::string const& id);
std::string const& GetString(std::string const& locale, std::string const& id);

//-----------------------------------------------------------------------------

} // namespace Localization
} // namespace SimCache
