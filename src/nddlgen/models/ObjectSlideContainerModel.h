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

#ifndef NDDLGEN_MODELS_OBJECTSLIDECONTAINERMODEL_H_
#define NDDLGEN_MODELS_OBJECTSLIDECONTAINERMODEL_H_

#include <nddlgen/models/AbstractObjectModel.h>
#include <iostream>
#include <fstream>

#include <nddlgen/models/ObjectSlideContainerStateModel.h>
#include <nddlgen/models/ProcessModel.h>
#include <nddlgen/models/ActionModel.h>
#include <nddlgen/utilities/WriteStream.hpp>

namespace nddlgen
{
	namespace models
	{
		class ObjectSlideContainerModel;
	}
}

class nddlgen::models::ObjectSlideContainerModel : public nddlgen::models::AbstractObjectModel
{

	private:

		nddlgen::models::ObjectSlideContainerStateModelPtr _oscs;

		nddlgen::models::ActionModelPtr getFillObjectSlideContainerAction();
		nddlgen::models::ActionModelPtr getEmptyObjectSlideContainerAction();

	public:

		ObjectSlideContainerModel();
		virtual ~ObjectSlideContainerModel();

		virtual void initSubObjects();
		virtual void initActions();

};

#endif
