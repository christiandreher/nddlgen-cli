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

nddlgen::models::LidBoxModel::LidBoxModel()
{
	this->setClassName("LidBox");

	this->_openedPredicate = "opened";
	this->_closingPredicate = "closing";
	this->_closedPredicate = "closed";
	this->_openingPredicate = "opening";
}

nddlgen::models::LidBoxModel::~LidBoxModel()
{

}

void nddlgen::models::LidBoxModel::initPredicates()
{
	this->addPredicate(this->_openedPredicate);
	this->addPredicate(this->_closingPredicate);
	this->addPredicate(this->_closedPredicate);
	this->addPredicate(this->_openingPredicate);

	this->setInitialPredicate(this->_closedPredicate);
}

void nddlgen::models::LidBoxModel::initActions()
{
	this->addAction(this->getOpenAction());
	this->addAction(this->getCloseAction());
}

nddlgen::utilities::ModelActionPtr nddlgen::models::LidBoxModel::getOpenAction()
{
	nddlgen::utilities::ModelActionPtr openAction(new nddlgen::utilities::ModelAction());

	openAction->setName("open" + this->getNamePref());
	openAction->setDuration("1");
	openAction->addMetByCondition(this->getAccessor(), this->_closedPredicate);

	if (this->isBlocked())
	{
		foreach (nddlgen::models::NddlGeneratablePtr generatableModel, this->_blockedBy)
		{
			if (generatableModel->getClassName() == "Obstacle")
			{
				nddlgen::models::ObstacleModelPtr obstacle = boost::dynamic_pointer_cast<nddlgen::models::ObstacleModel>(
						generatableModel);

				openAction->addContainedByCondition(obstacle->getAccessor(), obstacle->getClearedPredicate());
			}
		}
	}

	openAction->addEqualsEffect(this->getAccessor(), this->_openingPredicate);
	openAction->addMeetsEffect(this->getAccessor(), this->_openedPredicate);

	return openAction;
}

nddlgen::utilities::ModelActionPtr nddlgen::models::LidBoxModel::getCloseAction()
{
	nddlgen::utilities::ModelActionPtr closeAction(new nddlgen::utilities::ModelAction());

	closeAction->setName("close" + this->getNamePref());
	closeAction->setDuration("1");
	closeAction->addMetByCondition(this->getAccessor(), this->_openedPredicate);
	closeAction->addEqualsEffect(this->getAccessor(), this->_closingPredicate);
	closeAction->addMeetsEffect(this->getAccessor(), this->_closedPredicate);

	return closeAction;
}

std::string nddlgen::models::LidBoxModel::getOpenedPredicate()
{
	return this->_openedPredicate;
}

std::string nddlgen::models::LidBoxModel::getClosingPredicate()
{
	return this->_closingPredicate;
}

std::string nddlgen::models::LidBoxModel::getClosedPredicate()
{
	return this->_closedPredicate;
}

std::string nddlgen::models::LidBoxModel::getOpeningPredicate()
{
	return this->_openingPredicate;
}
