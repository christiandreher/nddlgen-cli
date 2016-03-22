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

#ifndef NDDLGEN_MODELS_OBJECTSLIDECONTAINERSTATEMODEL_H_
#define NDDLGEN_MODELS_OBJECTSLIDECONTAINERSTATEMODEL_H_

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/AbstractObjectModel.h>

namespace nddlgen
{
	namespace models
	{
		class ObjectSlideContainerStateModel;
		typedef boost::shared_ptr<nddlgen::models::ObjectSlideContainerStateModel> ObjectSlideContainerStateModelPtr;
	}
}

class nddlgen::models::ObjectSlideContainerStateModel : public nddlgen::models::AbstractObjectModel
{

	private:

		std::string _fullPredicate;
		std::string _emptyingPredicate;
		std::string _emptyPredicate;
		std::string _fillingPredicate;

		nddlgen::models::ActionModelPtr getFillObjectSlideContainerAction();

		nddlgen::models::ActionModelPtr getEmptyObjectSlideContainerAction();

	public:

		ObjectSlideContainerStateModel();

		virtual ~ObjectSlideContainerStateModel();

		virtual void initPredicates();

		virtual void initActions();

		std::string getFullPredicate();
		std::string getEmptyingPredicate();
		std::string getEmptyPredicate();
		std::string getFillingPredicate();

};

#endif
