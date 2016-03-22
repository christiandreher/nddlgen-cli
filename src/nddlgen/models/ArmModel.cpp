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

#include <nddlgen/models/ArmModel.h>

nddlgen::models::ArmModel::ArmModel()
{

}

nddlgen::models::ArmModel::~ArmModel()
{

}

void nddlgen::models::ArmModel::initActions()
{
	this->addAction(this->preparationProcess1Action());
	this->addAction(this->preparationProcess2Action());
	this->addAction(this->goalAchievedAction());
}

nddlgen::models::ActionModelPtr nddlgen::models::ArmModel::preparationProcess1Action()
{
	nddlgen::models::ActionModelPtr action(new nddlgen::models::ActionModel());

	nddlgen::models::LidBoxModelPtr lidbox1 = boost::dynamic_pointer_cast<nddlgen::models::LidBoxModel>(
			this->getSubObjectByName("unit_lidbox_1", true));
	nddlgen::models::LidBoxModelPtr lidbox2 = boost::dynamic_pointer_cast<nddlgen::models::LidBoxModel>(
			this->getSubObjectByName("unit_lidbox_2", true));
	nddlgen::models::ObjectSlideContainerStateModelPtr oscs = boost::dynamic_pointer_cast<nddlgen::models::ObjectSlideContainerStateModel>(
			this->getSubObjectByName("oscs", true));
	nddlgen::models::ProcessModelPtr prepProcess1 = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("preparation_process_1", true));
	nddlgen::models::ProcessModelPtr prepProcess2 = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("preparation_process_2", true));

	action->setName("prepare_objectslidecontainer_1");
	action->setDuration("3");

	action->addContainedByCondition(lidbox1->getAccessor(), lidbox1->getOpenedPredicate());
	action->addContainedByCondition(lidbox2->getAccessor(), lidbox2->getClosedPredicate());
	action->addContainedByCondition(oscs->getAccessor(), oscs->getFullPredicate());
	action->addContainedByCondition(prepProcess2->getAccessor(), prepProcess2->getPendingPredicate());

	action->addMetByCondition(prepProcess1->getAccessor(), prepProcess1->getPendingPredicate());
	action->addEqualsEffect(prepProcess1->getAccessor(), prepProcess1->getProcessingPredicate());
	action->addMeetsEffect(prepProcess1->getAccessor(), prepProcess1->getDonePredicate());

	action->addMeetsCondition(lidbox1->getAccessor(), lidbox1->getClosingPredicate());

	return action;
}

nddlgen::models::ActionModelPtr nddlgen::models::ArmModel::preparationProcess2Action()
{
	nddlgen::models::ActionModelPtr action(new nddlgen::models::ActionModel());

	nddlgen::models::LidBoxModelPtr lidbox1 = boost::dynamic_pointer_cast<nddlgen::models::LidBoxModel>(
			this->getSubObjectByName("unit_lidbox_1", true));
	nddlgen::models::LidBoxModelPtr lidbox2 = boost::dynamic_pointer_cast<nddlgen::models::LidBoxModel>(
			this->getSubObjectByName("unit_lidbox_2", true));
	nddlgen::models::ObjectSlideContainerStateModelPtr oscs = boost::dynamic_pointer_cast<nddlgen::models::ObjectSlideContainerStateModel>(
			this->getSubObjectByName("oscs", true));
	nddlgen::models::ProcessModelPtr prepProcess1 = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("preparation_process_1", true));
	nddlgen::models::ProcessModelPtr prepProcess2 = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("preparation_process_2", true));

	action->setName("prepare_objectslidecontainer_2");
	action->setDuration("3");

	action->addContainedByCondition(lidbox1->getAccessor(), lidbox1->getClosedPredicate());
	action->addContainedByCondition(lidbox2->getAccessor(), lidbox2->getOpenedPredicate());
	action->addContainedByCondition(oscs->getAccessor(), oscs->getFullPredicate());
	action->addContainedByCondition(prepProcess1->getAccessor(), prepProcess1->getDonePredicate());

	action->addMetByCondition(prepProcess2->getAccessor(), prepProcess2->getPendingPredicate());
	action->addEqualsEffect(prepProcess2->getAccessor(), prepProcess2->getProcessingPredicate());
	action->addMeetsEffect(prepProcess2->getAccessor(), prepProcess2->getDonePredicate());

	action->addMeetsCondition(lidbox2->getAccessor(), lidbox2->getClosingPredicate());

	return action;
}

nddlgen::models::ActionModelPtr nddlgen::models::ArmModel::goalAchievedAction()
{
	nddlgen::models::ActionModelPtr action(new nddlgen::models::ActionModel());

	nddlgen::models::ProcessModelPtr armProcess = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("armprocess"));
	nddlgen::models::ObjectSlideContainerStateModelPtr oscs = boost::dynamic_pointer_cast<nddlgen::models::ObjectSlideContainerStateModel>(
			this->getSubObjectByName("oscs", true));
	nddlgen::models::ProcessModelPtr prepProcess1 = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("preparation_process_1", true));
	nddlgen::models::ProcessModelPtr prepProcess2 = boost::dynamic_pointer_cast<nddlgen::models::ProcessModel>(
			this->getSubObjectByName("preparation_process_2", true));

	action->setName("goal_achieved");
	action->setDuration("1");

	action->addContainedByCondition(prepProcess1->getAccessor(), prepProcess1->getDonePredicate());
	action->addContainedByCondition(prepProcess2->getAccessor(), prepProcess2->getDonePredicate());
	action->addContainedByCondition(oscs->getAccessor(), oscs->getEmptyPredicate());

	action->addMetByCondition(armProcess->getAccessor(), armProcess->getPendingPredicate());
	action->addEqualsEffect(armProcess->getAccessor(), armProcess->getProcessingPredicate());
	action->addMeetsEffect(armProcess->getAccessor(), armProcess->getDonePredicate());

	return action;
}
