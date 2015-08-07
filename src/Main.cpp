/**
 * Copyright 2015 Christian Dreher (dreher@charlydelta.org)
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

#include <nddlgen/Controller.h>

int processArguments(int argc, char* argv[]);
std::string getOptionValue(int argc, char* argv[], std::string longOptionName, std::string shortOptionName);
bool isOptionSet(int argc, char* argv[], std::string longOptionName, std::string shortOptionName);

void printUsage(std::string calledName);
void printLicense();
void print(std::string);
void printNewLine();
void printNewLine(std::string);

std::string color(std::string text, int colorCode);
std::string red(std::string text);
std::string green(std::string text);
std::string yellow(std::string text);
std::string blue(std::string text);

std::string _nddlgenCliVersion = "2.0.1";
std::string _infile = "";
std::string _outpath = "";
bool _verbose = false;

int main(int argc, char* argv[])
{
	int processCode = processArguments(argc, argv);

	if (processCode == -1)
	{
		return EXIT_FAILURE;
	}
	else if (processCode == 1)
	{
		return EXIT_SUCCESS;
	}

	nddlgen::Controller* c = new nddlgen::Controller();

	c->setAdapter("nddlgen-cli v" + _nddlgenCliVersion);

	if (_outpath != "")
	{
		c->setOutputFilesPath(_outpath);
	}

	printNewLine(yellow("nddlgen-cli v" + _nddlgenCliVersion + " using nddlgen-core v"
			+ nddlgen::utilities::Meta::NDDLGEN_VERSION));

	printLicense();

	try
	{
		printNewLine("Processing file\t\t\t\t" + yellow(_infile));

		print("Checking file...\t\t\t");
		c->setFileIdentifier(_infile);
		c->checkFile();
		printNewLine(green("[OK]"));

		print("Parsing SDF...\t\t\t\t");
		c->parseSdf();
		printNewLine(green("[OK]"));

		print("Generating NDDL files...\t\t");
		c->generateNddl();
		printNewLine(green("[OK]"));
		printNewLine();

		printNewLine(green("NDDL files successfully generated."));
		printNewLine();

		printNewLine("Saving files in path \t\t\t" + yellow(c->getOutputFilesPath()));
		printNewLine("Domain models saved as \t\t\t" + yellow(c->getModelsOutputFileName()));
		printNewLine("Domain initial state saved as \t\t" + yellow(c->getInitialStateOutputFileName()));

		boost::checked_delete(c);

		return EXIT_SUCCESS;
	}
	catch (const std::exception& e)
	{
		std::string errorMsg = e.what();

		printNewLine(red("[FAIL]"));

		if (_verbose)
		{
			std::cout << std::flush;
			std::cerr << std::endl << red("Error. " + errorMsg) << std::endl;
		}
		else
		{
			std::cerr << "Error. " << errorMsg << std::endl;
		}

		boost::checked_delete(c);

		return EXIT_FAILURE;
	}

}


int processArguments(int argc, char* argv[])
{
	std::string calledName(argv[0]);

	bool help = isOptionSet(argc, argv, "help", "h");
	bool coreVersion = isOptionSet(argc, argv, "core-version", "c");
	bool version = isOptionSet(argc, argv, "version", "v");
	bool verbose = isOptionSet(argc, argv, "verbose", "b");

	std::string infile = getOptionValue(argc, argv, "infile", "i");
	std::string outpath = getOptionValue(argc, argv, "outpath", "o");

	if (argc == 1)
	{
		printUsage(calledName);
		return -1;
	}

	if (help)
	{
		printUsage(calledName);
		return 1;
	}

	if (coreVersion)
	{
		std::cout << nddlgen::utilities::Meta::NDDLGEN_VERSION << std::endl;
		return 1;
	}

	if (version)
	{
		std::cout << _nddlgenCliVersion << std::endl;
		return 1;
	}

	if (verbose)
	{
		_verbose = true;
	}

	if (infile != "")
	{
		_infile = infile;
	}
	else
	{
		printUsage(calledName);
		return -1;
	}

	if (outpath != "")
	{
		_outpath = outpath;
	}

	return 0;
}

std::string getOptionValue(int argc, char* argv[], std::string longOptionName, std::string shortOptionName)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		if (arg == "--" + longOptionName || arg == "-" + shortOptionName)
		{
			if (i + 1 == argc)
			{
				return "";
			}

			return argv[i + 1];
		}
	}

	return "";
}

bool isOptionSet(int argc, char* argv[], std::string longOptionName, std::string shortOptionName)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		if (arg == "--" + longOptionName || arg == "-" + shortOptionName)
		{
			return true;
		}
	}

	return false;
}


void printUsage(std::string calledName)
{
	std::cout << "nddlgen-cli v" << _nddlgenCliVersion << " using nddlgen-core v"
			<< nddlgen::utilities::Meta::NDDLGEN_VERSION << std::endl;
	std::cout << "nddlgen is a program suite to generate .nddl files out of Gazebo's .sdf"
			<< std::endl << std::endl;

	std::cout << "Usage:" << std::endl;
	std::cout << "  " << calledName << " [options] --infile <input_file> [--outpath <output_path>]"
			<< std::endl << std::endl;

	std::cout << "Options:" << std::endl;
	std::cout << "  --help, -h - Print help" << std::endl;
	std::cout << "  --core-version, -c - Version of nddlgen-core" << std::endl;
	std::cout << "  --version, -v - Version of nddlgen-cli" << std::endl;
	std::cout << "  --verbose, -b - Verbose output" << std::endl << std::endl;

	std::cout << "Arguments:" << std::endl;
	std::cout << "  --infile, -i - Input file (relative or absolute). Mandatory." << std::endl;
	std::cout << "  --outpath, -o - Output path (relative or absolute). If not set, the path of --infile is used" << std::endl;
}

void printLicense()
{
	if (_verbose)
	{
		std::cout << std::endl;
		std::cout << blue("  Copyright 2015 Christian Dreher (dreher@charlydelta.org)") << std::endl;
		std::cout << blue(" ") << std::endl;
		std::cout << blue("  Licensed under the Apache License, Version 2.0 (the \"License\");") << std::endl;
		std::cout << blue("  you may not use this file except in compliance with the License.") << std::endl;
		std::cout << blue("  You may obtain a copy of the License at") << std::endl;
		std::cout << blue(" ") << std::endl;
		std::cout << blue("  \thttp://www.apache.org/licenses/LICENSE-2.0") << std::endl;
		std::cout << blue(" ") << std::endl;
		std::cout << blue("  Unless required by applicable law or agreed to in writing, software") << std::endl;
		std::cout << blue("  distributed under the License is distributed on an \"AS IS\" BASIS,") << std::endl;
		std::cout << blue("  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.") << std::endl;
		std::cout << blue("  See the License for the specific language governing permissions and") << std::endl;
		std::cout << blue("  limitations under the License.") << std::endl << std::endl;
	}
}

void print(std::string text)
{
	if (_verbose)
	{
		std::cout << text;
	}
}

void printNewLine()
{
	if (_verbose)
	{
		printNewLine("");
	}
}

void printNewLine(std::string text)
{
	if (_verbose)
	{
		std::cout << text << std::endl;
	}
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
