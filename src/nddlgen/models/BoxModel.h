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

#ifndef NDDLGEN_MODELS_BOXMODEL_H_
#define NDDLGEN_MODELS_BOXMODEL_H_

#include <iostream>
#include <fstream>

#include <nddlgen/models/NddlGeneratable.h>

namespace nddlgen
{
	namespace models
	{
		class BoxModel;
	}
}

class nddlgen::models::BoxModel : public nddlgen::models::NddlGeneratable
{

	public:

		BoxModel();
		virtual ~BoxModel();

};

#endif
