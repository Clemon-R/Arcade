/*
** EPITECH PROJECT, 2018
** arcades
** File description:
** Exception
*/

#include "Exception.hpp"

Exception::Exception(const std::string &txt) : _txt(txt)
{
}

const char	*Exception::what() const noexcept
{
	return (_txt.c_str());
}
