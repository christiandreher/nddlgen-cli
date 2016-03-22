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

#ifndef NDDLGEN_CONTROLLERS_OBJECTFACTORY_H_
#define NDDLGEN_CONTROLLERS_OBJECTFACTORY_H_

#include <boost/shared_ptr.hpp>

#include <nddlgen/models/ArmModel.h>
#include <nddlgen/models/BoxModel.h>
#include <nddlgen/models/DomainDescriptionModel.h>
#include <nddlgen/models/LidBoxModel.h>
#include <nddlgen/models/ObjectSlideContainerModel.h>
#include <nddlgen/models/ObjectSlideModel.h>
#include <nddlgen/models/ObstacleModel.h>
#include <nddlgen/controllers/AbstractObjectFactory.h>
#include <nddlgen/models/AbstractObjectModel.h>
#include <nddlgen/models/DefaultArmModel.h>
#include <nddlgen/models/ActionModel.h>

namespace nddlgen
{
	namespace controllers
	{
		class ObjectFactory;
		typedef boost::shared_ptr<nddlgen::controllers::ObjectFactory> ObjectFactoryPtr;
	}
}

class nddlgen::controllers::ObjectFactory : public nddlgen::controllers::AbstractObjectFactory
{

	public:

		ObjectFactory();
		virtual ~ObjectFactory();

		virtual void registerObjectModels();

		static nddlgen::models::AbstractObjectModelPtr createArm();
		static nddlgen::models::AbstractObjectModelPtr createBox();
		static nddlgen::models::AbstractObjectModelPtr createLidBox();
		static nddlgen::models::AbstractObjectModelPtr createObjectSlideContainer();
		static nddlgen::models::AbstractObjectModelPtr createObjectSlide();
		static nddlgen::models::AbstractObjectModelPtr createObstacle();

};

#endif
