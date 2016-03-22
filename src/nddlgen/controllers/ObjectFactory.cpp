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

#include <nddlgen/controllers/ObjectFactory.h>

nddlgen::controllers::ObjectFactory::ObjectFactory()
{

}

nddlgen::controllers::ObjectFactory::~ObjectFactory()
{

}

void nddlgen::controllers::ObjectFactory::registerObjectModels()
{
	// Order of registration is arbitrary. Model names don't have to be prefix free
	this->registerObjectModel("Arm", &nddlgen::controllers::ObjectFactory::createArm);
	this->registerObjectModel("Workspace", &nddlgen::controllers::AbstractObjectFactory::createDefaultWorkspace);
	this->registerObjectModel("Box", &nddlgen::controllers::ObjectFactory::createBox);
	this->registerObjectModel("LidBox", &nddlgen::controllers::ObjectFactory::createLidBox);
	this->registerObjectModel("ObjectSlide", &nddlgen::controllers::ObjectFactory::createObjectSlide);
	this->registerObjectModel("ObjectSlideContainer", &nddlgen::controllers::ObjectFactory::createObjectSlideContainer);
	this->registerObjectModel("Obstacle", &nddlgen::controllers::ObjectFactory::createObstacle);
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::ObjectFactory::createArm()
{
	nddlgen::models::AbstractObjectModelPtr model(new nddlgen::models::ArmModel());
	return model;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::ObjectFactory::createBox()
{
	nddlgen::models::AbstractObjectModelPtr model(new nddlgen::models::BoxModel());
	return model;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::ObjectFactory::createLidBox()
{
	nddlgen::models::AbstractObjectModelPtr model(new nddlgen::models::LidBoxModel());
	return model;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::ObjectFactory::createObjectSlideContainer()
{
	nddlgen::models::AbstractObjectModelPtr model(new nddlgen::models::ObjectSlideContainerModel());
	return model;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::ObjectFactory::createObjectSlide()
{
	nddlgen::models::AbstractObjectModelPtr model(new nddlgen::models::ObjectSlideModel());
	return model;
}

nddlgen::models::AbstractObjectModelPtr nddlgen::controllers::ObjectFactory::createObstacle()
{
	nddlgen::models::AbstractObjectModelPtr model(new nddlgen::models::ObstacleModel());
	return model;
}
