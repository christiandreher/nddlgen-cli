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

#ifndef NDDLGEN_MODELS_LIDBOXMODEL_H_
#define NDDLGEN_MODELS_LIDBOXMODEL_H_

#include <iostream>
#include <fstream>

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/BoxModel.h>
#include <nddlgen/models/ObstacleModel.h>

namespace nddlgen
{
	namespace models
	{
		class LidBoxModel;
		typedef boost::shared_ptr<nddlgen::models::LidBoxModel> LidBoxModelPtr;
	}
}

class nddlgen::models::LidBoxModel : public nddlgen::models::BoxModel
{

	private:

		std::string _openedPredicate;
		std::string _closingPredicate;
		std::string _closedPredicate;
		std::string _openingPredicate;

		nddlgen::models::ActionModelPtr getOpenAction();
		nddlgen::models::ActionModelPtr getCloseAction();

	public:

		LidBoxModel();
		virtual ~LidBoxModel();

		virtual void initPredicates();
		virtual void initActions();

		std::string getOpenedPredicate();
		std::string getClosingPredicate();
		std::string getClosedPredicate();
		std::string getOpeningPredicate();

};

#endif
