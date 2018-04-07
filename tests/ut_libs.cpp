/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** ut_libs
*/

#include <criterion/criterion.h>
#include "Launcher.hpp"

Test(Launcher, load_libs_empty)
{
	std::string	lib("");
	Launcher	*launcher = new Launcher(lib);

	if (launcher)
		delete launcher;
}

Test(Launcher, load_libs_dont_exist)
{
	std::string	lib("mamene");
	Launcher	*launcher = new Launcher(lib);

	if (launcher)
		delete launcher;
}