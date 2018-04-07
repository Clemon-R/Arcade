/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** main
*/
#include "Graphic.hpp"
#include "Launcher.hpp"
#include "Exception.hpp"
#include <memory>
#include <iostream>
#include <dlfcn.h>

static void     usage()
{
    std::cout << "INPUT\n";
    std::cout << "\tlib_path\tthe path of the lib to use.\n";
}

int main(int argc, char **argv)
{
    std::unique_ptr<Launcher>   launcher = nullptr;
    std::string lib;

    if (argc != 2 || argv[1] == "-h"){
        usage();
        return (argv[1] == "-h" ? 0 : 84);
    }
    lib = std::string(argv[1]);
	try{
		launcher.reset(new Launcher(lib));
		launcher->start();
	}
	catch (const Exception &err){
		std::cerr << err.what() << std::endl;
	}
    return (0);
}