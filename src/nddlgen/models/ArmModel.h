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

#ifndef NDDLGEN_MODELS_ARMMODEL_H_
#define NDDLGEN_MODELS_ARMMODEL_H_

#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/DefaultArmModel.h>
#include <nddlgen/models/LidBoxModel.h>
#include <nddlgen/models/ObjectSlideContainerStateModel.h>
#include <nddlgen/models/ProcessModel.h>

namespace nddlgen
{
	namespace models
	{
		class ArmModel;
		typedef boost::shared_ptr<nddlgen::models::ArmModel> ArmModelPtr;
	}
}

class nddlgen::models::ArmModel : public nddlgen::models::DefaultArmModel
{

	private:

		nddlgen::models::ActionModelPtr preparationProcess1Action();

		nddlgen::models::ActionModelPtr preparationProcess2Action();

		nddlgen::models::ActionModelPtr goalAchievedAction();

	public:

		ArmModel();

		virtual ~ArmModel();

		virtual void initActions();

};

#endif
