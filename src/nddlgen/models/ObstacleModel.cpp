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

#include <nddlgen/models/ObstacleModel.h>

nddlgen::models::ObstacleModel::ObstacleModel()
{
	this->setClassName("Obstacle");

	this->_blockingPredicate = "blocking";
	this->_beingClearedPredicate = "being_cleared";
	this->_clearedPredicate = "cleared";
}

nddlgen::models::ObstacleModel::~ObstacleModel()
{

}

void nddlgen::models::ObstacleModel::initPredicates()
{
	this->addPredicate(this->_blockingPredicate);
	this->addPredicate(this->_beingClearedPredicate);
	this->addPredicate(this->_clearedPredicate);

	this->setInitialPredicate(this->_blockingPredicate);
}

void nddlgen::models::ObstacleModel::initActions()
{
	nddlgen::models::ActionModelPtr clearObstacleAction(new nddlgen::models::ActionModel());

	clearObstacleAction->setName("clear_" + this->getName());
	clearObstacleAction->setDuration("2");

	if (this->hasBlockingObjects())
	{
		foreach (nddlgen::models::AbstractObjectModelPtr generatableModel, this->_blockingObjects)
		{
			if (generatableModel->getClassName() == "Obstacle")
			{
				nddlgen::models::ObstacleModelPtr obstacle = boost::dynamic_pointer_cast<nddlgen::models::ObstacleModel>(
						generatableModel);

				clearObstacleAction->addContainedByCondition(obstacle->getAccessor(), obstacle->getClearedPredicate());
			}
		}
	}

	clearObstacleAction->addMetByCondition(this->getAccessor(), this->_blockingPredicate);
	clearObstacleAction->addEqualsEffect(this->getAccessor(), this->_beingClearedPredicate);
	clearObstacleAction->addMeetsEffect(this->getAccessor(), this->_clearedPredicate);

	this->addAction(clearObstacleAction);
}

std::string nddlgen::models::ObstacleModel::getBlockingPredicate()
{
	return this->_blockingPredicate;
}

std::string nddlgen::models::ObstacleModel::getBeingClearedPredicate()
{
	return this->_beingClearedPredicate;
}

std::string nddlgen::models::ObstacleModel::getClearedPredicate()
{
	return this->_clearedPredicate;
}
