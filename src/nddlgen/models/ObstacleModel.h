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

#ifndef NDDLGEN_MODELS_OBSTACLEMODEL_H_
#define NDDLGEN_MODELS_OBSTACLEMODEL_H_

#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/NddlGeneratable.h>

namespace nddlgen
{
	namespace models
	{
		class ObstacleModel;
		typedef boost::shared_ptr<nddlgen::models::ObstacleModel> ObstacleModelPtr;
	}
}

class nddlgen::models::ObstacleModel : public nddlgen::models::NddlGeneratable
{

	private:

		std::string _blockingPredicate;
		std::string _beingClearedPredicate;
		std::string _clearedPredicate;

	public:

		ObstacleModel();
		virtual ~ObstacleModel();

		virtual void initPredicates();
		virtual void initActions();

		std::string getBlockingPredicate();
		std::string getBeingClearedPredicate();
		std::string getClearedPredicate();

};

#endif
