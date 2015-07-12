/**
 * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <iostream>
#include <cstdlib>
#include <boost/lexical_cast.hpp>

#include "nddlgen/Controller.h"

void printLicense();
std::string color(std::string text, int colorCode);
std::string red(std::string text);
std::string green(std::string text);
std::string yellow(std::string text);
std::string blue(std::string text);
int die(std::string errorText);

int main(int argc, char* argv[])
{
	std::string errorText;
	std::string fileIdentifier;
	nddlgen::Controller* c = new nddlgen::Controller(&errorText);

	std::cout << yellow("nddl-generator-cli v1.0.0") << std::endl;

	printLicense();

	if (argc > 1)
	{
		fileIdentifier = std::string(argv[1]);
	}
	else
	{
		std::cout << "Enter file identifier: ";
		std::cin >> fileIdentifier;
	}

	std::cout << "Processing file\t\t\t\t" << yellow(fileIdentifier) << std::endl;

	std::cout << "Checking file...\t\t\t";

	if (!c->setFileIdentifier(fileIdentifier) || !c->checkFile())
	{
		std::cout << red("[FAIL]") << std::endl;
		return die(errorText);
	}

	std::cout << green("[OK]") << std::endl;
	std::cout << "Parsing SDF...\t\t\t\t";

	if (!c->parseSdf())
	{
		std::cout << red("[FAIL]") << std::endl;
		return die(errorText);
	}

	std::cout << green("[OK]") << std::endl;
	std::cout << "Generating NDDL files...\t\t";

	if (!c->generateNddl())
	{
		std::cout << red("[FAIL]") << std::endl;
		return die(errorText);
	}

	std::cout << green("[OK]") << std::endl << std::endl;

	std::cout << green("NDDL files successfully generated.") << std::endl << std::endl;

	std::cout << "Saving files in path \t\t\t" << yellow(c->getOutputFilesPath()) << std::endl;
	std::cout << "Domain models saved as \t\t\t" << yellow(c->getModelsOutputFileName()) << std::endl;
	std::cout << "Domain initial state saved as \t\t" << yellow(c->getInitialStateOutputFileName()) << std::endl;

	delete c;
	return EXIT_SUCCESS;
}

void printLicense()
{
	std::cout << std::endl;
	std::cout << blue(" * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)") << std::endl;
	std::cout << blue(" *") << std::endl;
	std::cout << blue(" * Licensed under the Apache License, Version 2.0 (the \"License\");") << std::endl;
	std::cout << blue(" * you may not use this file except in compliance with the License.") << std::endl;
	std::cout << blue(" * You may obtain a copy of the License at") << std::endl;
	std::cout << blue(" *") << std::endl;
	std::cout << blue(" * \thttp://www.apache.org/licenses/LICENSE-2.0") << std::endl;
	std::cout << blue(" *") << std::endl;
	std::cout << blue(" * Unless required by applicable law or agreed to in writing, software") << std::endl;
	std::cout << blue(" * distributed under the License is distributed on an \"AS IS\" BASIS,") << std::endl;
	std::cout << blue(" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.") << std::endl;
	std::cout << blue(" * See the License for the specific language governing permissions and") << std::endl;
	std::cout << blue(" * limitations under the License.") << std::endl << std::endl;
}

std::string color(std::string text, int colorCode)
{
	return "\033[1;3" + boost::lexical_cast<std::string>(colorCode) + "m" + text + "\033[0m";
}

std::string red(std::string text)
{
	return color(text, 1);
}

std::string green(std::string text)
{
	return color(text, 2);
}

std::string yellow(std::string text)
{
	return color(text, 3);
}

std::string blue(std::string text)
{
	return color(text, 4);
}

int die(std::string errorText)
{
	std::cout << std::flush;
	std::cerr << std::endl << red("Error. " + errorText) << std::endl;
	return EXIT_FAILURE;
}
