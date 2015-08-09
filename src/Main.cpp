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

#include <cstdlib>
#include <exception>
#include <iostream>

#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>

#include <nddlgen/Controller.h>
#include <nddlgen/exceptions/FileAlreadyExists.hpp>

// CLI argument helpers
void processArguments(int argc, char* argv[]);
std::string getOptionValue(int argc, char* argv[], std::string longOptionName);
bool isOptionSet(int argc, char* argv[], std::string longOptionName, std::string shortOptionName);

// Output helpers
void printUsage(std::string calledName);
void printHelp(std::string calledName);
void printUsageOrHelp(std::string calledName, bool help);
void printLicense();
void print(std::string);
void printNewLine();
void printNewLine(std::string);

// Coloring text helpers
std::string color(std::string text, int colorCode);
std::string red(std::string text);
std::string green(std::string text);
std::string yellow(std::string text);
std::string blue(std::string text);

// Version of nddlgen-cli
std::string _nddlgenCliVersion = "0.2.1";

// CLI arguments
bool _help = false;
bool _coreVersion = false;
bool _version = false;

std::string _inputSdfFile = "";
std::string _inputIsdFile = "";
std::string _outputPath = "";
bool _verbose = false;
bool _forceOverwrite = false;

int main(int argc, char* argv[])
{
	std::string calledName(argv[0]);

	// Check if program was called with arguments.
	if (argc == 1)
	{
		printUsage(calledName);
		return EXIT_FAILURE;
	}

	// Process arguments and initialize variables.
	processArguments(argc, argv);

	// Check if help was called.
	if (_help)
	{
		printHelp(calledName);
		return EXIT_SUCCESS;
	}

	// Check if version of core was requested.
	if (_coreVersion)
	{
		std::cout << nddlgen::utilities::Meta::NDDLGEN_VERSION << std::endl;
		return EXIT_SUCCESS;
	}

	// Check if nddlgen-cli verson was requested.
	if (_version)
	{
		std::cout << _nddlgenCliVersion << std::endl;
		return EXIT_SUCCESS;
	}

	// Check if mandatory parameters where set
	if (_inputSdfFile == "" || _inputIsdFile == "")
	{
		printUsage(calledName);
		return EXIT_FAILURE;
	}

	// Print header if verbose
	printNewLine(yellow("nddlgen-cli v" + _nddlgenCliVersion + " using nddlgen-core v"
			+ nddlgen::utilities::Meta::NDDLGEN_VERSION));

	// Print license header if verbose
	printLicense();

	// Create nddlgen controller
	nddlgen::Controller* c = new nddlgen::Controller();

	// Run the workflow. All outputs work only if verbose.
	// Catch any exceptions and print them (even if not verbose).
	try
	{
		// Initialize controller
		c->setAdapter("nddlgen-cli v" + _nddlgenCliVersion);
		c->setInputSdfFile(_inputSdfFile);
		c->setInputIsdFile(_inputIsdFile);
		c->setOutputFilesPath(_outputPath);

		printNewLine("Processing file\t\t\t\t\t" + yellow(c->getInputSdfFileName()));

		print("Checking SDF file...\t\t\t\t");
		c->checkSdfInput();
		printNewLine(green("[OK]"));

		print("Parsing SDF...\t\t\t\t\t");
		c->parseSdf();
		printNewLine(green("[OK]"));

		print("Generating NDDL model file...\t\t\t");

		try
		{
			c->generateNddlModel(_forceOverwrite);
		}
		catch(const nddlgen::exceptions::FileAlreadyExists& e)
		{
			std::string errorMessage(e.what());
			char overwrite;

			printNewLine(yellow("[WARN]"));
			printNewLine();

			if (_verbose)
			{
				std::cout << yellow("Warning. " + errorMessage) << std::endl << "Overwrite existing file? [y/N] ";
			}
			else
			{
				std::cout << "Warning. " << errorMessage << std::endl << "Overwrite existing file? [y/N] ";
			}

			overwrite = std::getchar();

			printNewLine();
			print("Overwriting existing NDDL model file...\t\t");

			if (overwrite == 'Y' || overwrite == 'y')
			{
				c->generateNddlModel(true);
			}
			else
			{

				throw std::runtime_error("Aborted due to user request.");
			}
		}

		printNewLine(green("[OK]"));

		printNewLine();
		printNewLine(green("NDDL model file successfully generated."));
		printNewLine();

		printNewLine("Processing file\t\t\t\t\t" + yellow(c->getInputIsdFileName()));

		print("Checking ISD file...\t\t\t\t");
		c->checkIsdInput();
		printNewLine(green("[OK]"));

		print("Parsing ISD...\t\t\t\t\t");
		c->parseIsd();
		printNewLine(green("[OK]"));

		print("Generating NDDL initial state file...\t\t");

		try
		{
			c->generateNddlInitialState(_forceOverwrite);
		}
		catch(const nddlgen::exceptions::FileAlreadyExists& e)
		{
			std::string errorMessage(e.what());
			char overwrite;

			printNewLine(yellow("[WARN]"));
			printNewLine();

			if (_verbose)
			{
				std::cout << yellow("Warning. " + errorMessage) << std::endl << "Overwrite existing file? [y/N] ";
			}
			else
			{
				std::cout << "Warning. " << errorMessage << std::endl << "Overwrite existing file? [y/N] ";
			}

			overwrite = std::getchar();

			printNewLine();
			print("Overwriting existing NDDL initial state file...\t\t");

			if (overwrite == 'Y' || overwrite == 'y')
			{
				c->generateNddlInitialState(true);
			}
			else
			{

				throw std::runtime_error("Aborted due to user request.");
			}
		}

		printNewLine(green("[OK]"));

		printNewLine();
		printNewLine(green("NDDL initial state file successfully generated."));
		printNewLine();

		printNewLine("Saved files in path \t\t\t" + yellow(c->getOutputFilesPath()));
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


void processArguments(int argc, char* argv[])
{
	_help = isOptionSet(argc, argv, "help", "h");
	_coreVersion = isOptionSet(argc, argv, "core-version", "c");
	_version = isOptionSet(argc, argv, "version", "v");

	_verbose = isOptionSet(argc, argv, "verbose", "x");
	_forceOverwrite = isOptionSet(argc, argv, "force-overwrite", "f");
	_inputSdfFile = getOptionValue(argc, argv, "in-sdf");
	_inputIsdFile = getOptionValue(argc, argv, "in-isd");
	_outputPath = getOptionValue(argc, argv, "out-path");
}

std::string getOptionValue(int argc, char* argv[], std::string longOptionName)
{
	for (int i = 1; i < argc; i++)
	{
		std::string arg = argv[i];

		if (arg == "--" + longOptionName)
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
		else if (!boost::starts_with(arg, "--") && boost::starts_with(arg, "-")
			&& boost::contains(arg, shortOptionName))
		{
			return true;
		}
	}

	return false;
}


void printUsage(std::string calledName)
{
	printUsageOrHelp(calledName, false);
}

void printHelp(std::string calledName)
{
	printUsageOrHelp(calledName, true);
}

void printUsageOrHelp(std::string calledName, bool help)
{
	std::cout << "nddlgen-cli v" << _nddlgenCliVersion << " using nddlgen-core v"
			<< nddlgen::utilities::Meta::NDDLGEN_VERSION << std::endl;
	std::cout << "nddlgen is a program suite to generate .nddl files out of Gazebo's .sdf"
			<< std::endl << std::endl;

	std::cout << "Usage:" << std::endl;
	std::cout << "  " << calledName << " [options] --in-sdf <sdf_file> --in-isd <isd_file> [--out-path <output_path>]"
			<< std::endl << std::endl;

	if (help)
	{
		std::cout << "Options:" << std::endl;
		std::cout << "  --help, -h Print help" << std::endl;
		std::cout << "  --core-version, -c Version of nddlgen-core" << std::endl;
		std::cout << "  --version, -v Version of nddlgen-cli" << std::endl;
		std::cout << "  --verbose, -x Verbose output" << std::endl;
		std::cout << "  --force-overwrite, f Force overwrite if files exist" << std::endl << std::endl;

		std::cout << "Arguments:" << std::endl;
		std::cout << "  --in-sdf Input SDF file (relative or absolute). Mandatory." << std::endl;
		std::cout << "  --in-isd Input ISD file (relative or absolute). Mandatory." << std::endl;
		std::cout << "  --out-path Output path (relative or absolute). If not set, the path of --infile is used"
				<< std::endl << std::endl;
	}
	else
	{
		std::cout << "For more help, type:" << std::endl;
		std::cout << "  " << calledName << " -h" << std::endl << std::endl;
	}

	std::cout << "nddlgen Homepage:" << std::endl;
	std::cout << "  <" << nddlgen::utilities::Meta::NDDLGEN_PROJECT_HOMEPAGE << ">" << std::endl;
	std::cout << "Author:" << std::endl;
	std::cout << "  Christian Dreher <" << nddlgen::utilities::Meta::AUTHOR_CHR_DREHER_EMAIL << ">" << std::endl;
	std::cout << "Support:" << std::endl;
	std::cout << "  <" << nddlgen::utilities::Meta::NDDLGEN_SUPPORT_EMAIL << ">" << std::endl;
}

void printLicense()
{
	if (_verbose)
	{
		std::cout << std::endl;
		std::cout << blue("  Copyright 2015 Christian Dreher (dreher@charlydelta.org)") << std::endl;
		std::cout << blue(" ") << std::endl;
		std::cout << blue("  This software is distributed on an \"AS IS\" BASIS, WITHOUT") << std::endl;
		std::cout << blue("  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.") << std::endl;
		std::cout << std::endl;
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
