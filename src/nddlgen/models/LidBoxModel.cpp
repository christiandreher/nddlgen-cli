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

#include <nddlgen/models/LidBoxModel.h>

namespace nddlgen { namespace models
{

	LidBoxModel::LidBoxModel()
	{
		this->setClassName("LidBox");

		this->_isOpened = false;
	}

	LidBoxModel::LidBoxModel(bool isOpened)
	{
		this->setClassName("LidBox");

		this->_isOpened = isOpened;
	}

	LidBoxModel::~LidBoxModel()
	{

	}


	void LidBoxModel::postInitProcessing()
	{
		std::string openedPredicate = "opened";
		std::string closedPredicate = "closed";

		nddlgen::utilities::ModelActionPtr openAction(new nddlgen::utilities::ModelAction());
		nddlgen::utilities::ModelActionPtr closeAction(new nddlgen::utilities::ModelAction());

		this->setClassName("LidBox");

		openAction->setName("open" + this->getNamePref());
		openAction->setDuration("1");
		openAction->setMetByCondition(this->getNamePref(), closedPredicate);

		if (this->isBlocked())
		{
			foreach (nddlgen::models::NddlGeneratablePtr generatableModel, this->_blockedBy)
			{
				openAction->setContainedByCondition(generatableModel->getNamePref(), closedPredicate);
			}
		}

		openAction->setMeetsEffect(this->getNamePref(), openedPredicate);

		closeAction->setName("close" + this->getNamePref());
		closeAction->setDuration("1");
		closeAction->setMetByCondition(this->getNamePref(), openedPredicate);
		closeAction->setMeetsEffect(this->getNamePref(), closedPredicate);

		this->addPredicate(openedPredicate);
		this->addPredicate(closedPredicate);

		this->addAction(openAction);
		this->addAction(closeAction);
	}


	void LidBoxModel::generateInitialState(std::ofstream& ofStream)
	{

	}


	bool LidBoxModel::isOpened()
	{
		return this->_isOpened;
	}

}}
