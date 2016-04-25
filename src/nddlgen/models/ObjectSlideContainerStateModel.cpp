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

#include <nddlgen/models/ObjectSlideContainerStateModel.h>

nddlgen::models::ObjectSlideContainerStateModel::ObjectSlideContainerStateModel()
{
	this->setClassName("ObjectSlideContainerState");

	this->_fullPredicate = "full";
	this->_emptyingPredicate = "emptying";
	this->_emptyPredicate = "empty";
	this->_fillingPredicate = "filling";
}

nddlgen::models::ObjectSlideContainerStateModel::~ObjectSlideContainerStateModel()
{

}

void nddlgen::models::ObjectSlideContainerStateModel::initPredicates()
{
	this->addPredicate(this->_fullPredicate);
	this->addPredicate(this->_emptyingPredicate);
	this->addPredicate(this->_emptyPredicate);
	this->addPredicate(this->_fillingPredicate);

	this->setInitialPredicate(this->_emptyPredicate);
}

std::string nddlgen::models::ObjectSlideContainerStateModel::getFullPredicate()
{
	return this->_fullPredicate;
}

std::string nddlgen::models::ObjectSlideContainerStateModel::getEmptyingPredicate()
{
	return this->_emptyingPredicate;
}

std::string nddlgen::models::ObjectSlideContainerStateModel::getEmptyPredicate()
{
	return this->_emptyPredicate;
}

std::string nddlgen::models::ObjectSlideContainerStateModel::getFillingPredicate()
{
	return this->_fillingPredicate;
}
