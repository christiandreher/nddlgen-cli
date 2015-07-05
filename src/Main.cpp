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

#include "base/Controller.h"

using namespace std;
using namespace base;

void printLicense();
string color(string text, int colorCode);
string red(string text);
string green(string text);
string yellow(string text);
string blue(string text);
int die(string errorText);

int main(int argc, char* argv[]) {
	string errorText;
	string fileIdentifier;
	Controller* c = new Controller(&errorText);

	cout << yellow("nddl-generator-cli v1.0.0") << endl;

	printLicense();

	if (argc > 1)
	{
		fileIdentifier = string(argv[1]);
	}
	else
	{
		cout << "Enter file identifier: ";
		cin >> fileIdentifier;
	}

	cout << "Processing \"" << yellow(fileIdentifier) << "\"..." << endl;

	cout << "Checking file...\t\t";

	if (!c->setFileIdentifier(fileIdentifier) || !c->checkFile())
	{
		cout << red("[FAIL]") << endl;
		return die(errorText);
	}

	cout << green("[OK]") << endl;
	cout << "Parsing file...\t\t\t";

	if (!c->parseSdf())
	{
		cout << red("[FAIL]") << endl;
		return die(errorText);
	}

	cout << green("[OK]") << endl;
	cout << "Generating NDDL file...\t\t";

	if (!c->generateNddl())
	{
		cout << red("[FAIL]") << endl;
		return die(errorText);
	}

	cout << green("[OK]") << endl;
	cout << "NDDL file successfully generated. Saved as \"" << yellow(c->getOutputFileName()) << "\"." << endl;

	delete c;
	return EXIT_SUCCESS;
}

void printLicense()
{
	cout << endl;
	cout << blue(" * Copyright 2015 Christian Dreher (christian.dreher@student.kit.edu)") << endl;
	cout << blue(" *") << endl;
	cout << blue(" * Licensed under the Apache License, Version 2.0 (the \"License\");") << endl;
	cout << blue(" * you may not use this file except in compliance with the License.") << endl;
	cout << blue(" * You may obtain a copy of the License at") << endl;
	cout << blue(" *") << endl;
	cout << blue(" * \thttp://www.apache.org/licenses/LICENSE-2.0") << endl;
	cout << blue(" *") << endl;
	cout << blue(" * Unless required by applicable law or agreed to in writing, software") << endl;
	cout << blue(" * distributed under the License is distributed on an \"AS IS\" BASIS,") << endl;
	cout << blue(" * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.") << endl;
	cout << blue(" * See the License for the specific language governing permissions and") << endl;
	cout << blue(" * limitations under the License.") << endl << endl;
}

string color(string text, int colorCode)
{
	return "\033[1;3" + boost::lexical_cast<string>(colorCode) + "m" + text + "\033[0m";
}

string red(string text)
{
	return color(text, 1);
}

string green(string text)
{
	return color(text, 2);
}

string yellow(string text)
{
	return color(text, 3);
}

string blue(string text)
{
	return color(text, 4);
}

int die(string errorText)
{
	cout << flush;
	cerr << red("Error. " + errorText) << endl;
	return EXIT_FAILURE;
}
