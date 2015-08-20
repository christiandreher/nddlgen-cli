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

#include <nddlgen/controllers/ModelFactory.h>

nddlgen::controllers::ModelFactory::ModelFactory()
{

}

nddlgen::controllers::ModelFactory::~ModelFactory()
{

}

void nddlgen::controllers::ModelFactory::registerNddlGeneratables()
{
	// Order of registration is arbitrary. Model names don't have to be prefix free
	this->registerNddlGeneratable("Box", &nddlgen::controllers::ModelFactory::createBox);
	this->registerNddlGeneratable("LidBox", &nddlgen::controllers::ModelFactory::createLidBox);
	this->registerNddlGeneratable("ObjectSlide", &nddlgen::controllers::ModelFactory::createObjectSlide);
	this->registerNddlGeneratable("ObjectSlideContainer", &nddlgen::controllers::ModelFactory::createObjectSlideContainer);
}

nddlgen::models::NddlGeneratable* nddlgen::controllers::ModelFactory::createBox()
{
	return new nddlgen::models::BoxModel();
}

nddlgen::models::NddlGeneratable* nddlgen::controllers::ModelFactory::createLidBox()
{
	return new nddlgen::models::LidBoxModel();
}

nddlgen::models::NddlGeneratable* nddlgen::controllers::ModelFactory::createObjectSlideContainer()
{
	return new nddlgen::models::ObjectSlideContainerModel();
}

nddlgen::models::NddlGeneratable* nddlgen::controllers::ModelFactory::createObjectSlide()
{
	return new nddlgen::models::ObjectSlideModel();
}
