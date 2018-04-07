/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** Exception
*/

#ifndef EXCEPTION_HPP_
	#define EXCEPTION_HPP_

	#include <exception>
	#include <iostream>

class Exception : public std::exception {
public:
	Exception(const std::string &txt);
	const char	*what() const noexcept override;
private:
	const std::string	_txt;
};

#endif /* !EXCEPTION_HPP_ */
