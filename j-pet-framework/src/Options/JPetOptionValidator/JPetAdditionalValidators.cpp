/**
 *  @copyright Copyright 2021 The J-PET Framework Authors. All rights reserved.
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may find a copy of the License in the LICENCE file.
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *  @file JPetAdditionalValiators.cpp
 */

#include "JPetOptionValidator/JPetAdditionalValidators.h"

#include <boost/any.hpp>

using boost::any_cast;

// cppcheck-suppress unusedFunction
bool additionalCheckIfRunIDIsOk(std::pair<std::string, boost::any> option)
{
  if (any_cast<int>(option.second) != 10)
  {
    return false;
  }
  return true;
}
