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
 *  @file JPetOptionValidatorTest.cpp
 */

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JPetOptionValidatorTest

#include "JPetOptionValidator/JPetOptionValidator.h"

#include <boost/test/unit_test.hpp>
#include <string>

using boost::any_cast;

BOOST_AUTO_TEST_SUITE(FirstSuite)

BOOST_AUTO_TEST_CASE(correctOptions)
{
  std::vector<int> range = {1, 2};
  std::vector<std::string> files = {"unitTestData/JPetCmdParserTest/data.hld", "unitTestData/JPetCmdParserTest/data.hld"};
  std::map<std::string, boost::any> options = {
      {"range_std::vector<int>", range},
      {"type_std::string", std::string("hld")},
      {"file_std::vector<std::string>", files},
      {"type_std::string, file_std::vector<std::string>", JPetOptionValidator::ManyOptionsWrapper({std::string("hld"), files})},
      {"localDB_std::string", std::string("unitTestData/JPetCmdParserTest/data.hld")},
      {"outputPath_std::string", std::string("unitTestData/JPetCmdParserTest")},
      {"runID_int", 3},
  };

  BOOST_REQUIRE(JPetOptionValidator::isOutputDirectoryValid(std::make_pair("outputPath_std::string", options.at("outputPath_std::string"))));
  BOOST_REQUIRE(JPetOptionValidator::isLocalDBValid(std::make_pair("localDB_std::string", options.at("localDB_std::string"))));
  BOOST_REQUIRE(JPetOptionValidator::isRunIDValid(std::make_pair("runID_int", options.at("runID_int"))));
  BOOST_REQUIRE(JPetOptionValidator::areFilesValid(std::make_pair("file_std::vector<std::string>", options.at("file_std::vector<std::string>"))));
  BOOST_REQUIRE(JPetOptionValidator::isCorrectFileType(std::make_pair("type_std::string", options.at("type_std::string"))));
  BOOST_REQUIRE(JPetOptionValidator::isFileTypeMatchingExtensions(
      std::make_pair("type_std::string, file_std::vector<std::string>", options.at("type_std::string, file_std::vector<std::string>"))));
  BOOST_REQUIRE(JPetOptionValidator::isRangeOfEventsValid(std::make_pair("range_std::vector<int>", options.at("range_std::vector<int>"))));
  BOOST_REQUIRE(JPetOptionValidator::isNumberBoundsInRangeValid(std::make_pair("range_std::vector<int>", options.at("range_std::vector<int>"))));
}

BOOST_AUTO_TEST_CASE(wrongOptions)
{
  std::vector<int> wrongRange = {4, 2, 3};
  std::vector<std::string> wrongFiles = {"ble/ble/ble.hld", "ble/ble/ble/ble/ble.hld"};
  std::map<std::string, boost::any> options = {
      {"range_std::vector<int>", wrongRange},
      {"type_std::string", std::string("tdt")},
      {"file_std::vector<std::string>", wrongFiles},
      {"type_std::string, file_std::vector<std::string>", JPetOptionValidator::ManyOptionsWrapper({std::string("tdt"), wrongFiles})},
      {"localDB_std::string", std::string("ble/ble/ble.hld")},
      {"outputPath_std::string", std::string("ble/ble/ble")},
      {"runID_int", -1},
      {"detectorType_std::string", std::string("squirrel")}};
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isRangeOfEventsValid(std::make_pair("range_std::vector<int>", options.at("range_std::vector<int>"))),
                      false);
  BOOST_REQUIRE_EQUAL(
      JPetOptionValidator::areFilesValid(std::make_pair("file_std::vector<std::string>", options.at("file_std::vector<std::string>"))), false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isOutputDirectoryValid(std::make_pair("outputPath_std::string", options.at("outputPath_std::string"))),
                      false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isLocalDBValid(std::make_pair("localDB_std::string", options.at("localDB_std::string"))), false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isRunIDValid(std::make_pair("runID_int", options.at("runID_int"))), false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isDetectorValid(std::make_pair("detectorType_std::string", options.at("detectorType_std::string"))),
                      false);
  BOOST_REQUIRE_EQUAL(
      JPetOptionValidator::areFilesValid(std::make_pair("file_std::vector<std::string>", options.at("file_std::vector<std::string>"))), false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isCorrectFileType(std::make_pair("type_std::string", options.at("type_std::string"))), false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isFileTypeMatchingExtensions(std::make_pair(
                          "type_std::string, file_std::vector<std::string>", options.at("type_std::string, file_std::vector<std::string>"))),
                      false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isRangeOfEventsValid(std::make_pair("range_std::vector<int>", options.at("range_std::vector<int>"))),
                      false);
  BOOST_REQUIRE_EQUAL(JPetOptionValidator::isNumberBoundsInRangeValid(std::make_pair("range_std::vector<int>", options.at("range_std::vector<int>"))),
                      false);
}

BOOST_AUTO_TEST_CASE(areCorrectAllOptionsWork)
{
  std::vector<int> range = {1, 2};
  std::vector<std::string> files = {"unitTestData/JPetCmdParserTest/data.hld", "unitTestData/JPetCmdParserTest/data.hld"};
  std::map<std::string, boost::any> options = {{"range_std::vector<int>", range},
                                               {"type_std::string", std::string("hld")},
                                               {"file_std::vector<std::string>", files},
                                               {"localDB_std::string", std::string("unitTestData/JPetCmdParserTest/data.hld")},
                                               {"outputPath_std::string", std::string("unitTestData/JPetCmdParserTest")},
                                               {"runID_int", 3},
                                               {"detectorType_std::string", std::string("barrel")}};
  JPetOptionValidator validator;
  std::vector<std::string> v;
  for (auto& opt : options)
  {
    v.push_back(opt.first);
  }
  v.push_back("type_std::string, file_std::vector<std::string>");
  options["ble"] = range;
  BOOST_REQUIRE(validator.areCorrectOptions(options, v));
}

BOOST_AUTO_TEST_CASE(areCorrectSomeOptionsWork)
{
  std::vector<int> range = {1, 2};
  std::map<std::string, boost::any> options = {
      {"range_std::vector<int>", range},
      {"type_std::string", std::string("hld")},
      {"localDB_std::string", std::string("unitTestData/JPetCmdParserTest/data.hld")},
      {"runID_int", 3},
  };

  JPetOptionValidator validator;
  std::vector<std::string> v;
  for (auto& opt : options)
  {
    v.push_back(opt.first);
  }
  options["ble"] = range;
  BOOST_REQUIRE(validator.areCorrectOptions(options, v));
}

BOOST_AUTO_TEST_CASE(areCorrectExtensions)
{
  std::string scopeType = "scope";
  std::string zipType = "zip";
  std::string whateverType = "whatever";
  std::vector<std::string> scopeResult = JPetOptionValidator::getCorrectExtensionsForTheType(scopeType);
  std::vector<std::string> zipResult = JPetOptionValidator::getCorrectExtensionsForTheType(zipType);
  std::vector<std::string> whateverResult = JPetOptionValidator::getCorrectExtensionsForTheType(whateverType);
  BOOST_REQUIRE(std::find(scopeResult.begin(), scopeResult.end(), ".json") != scopeResult.end());
  BOOST_REQUIRE(std::find(zipResult.begin(), zipResult.end(), ".gz") != zipResult.end());
  BOOST_REQUIRE(std::find(zipResult.begin(), zipResult.end(), ".xz") != zipResult.end());
  BOOST_REQUIRE(std::find(zipResult.begin(), zipResult.end(), ".bz2") != zipResult.end());
  BOOST_REQUIRE(std::find(zipResult.begin(), zipResult.end(), ".zip") != zipResult.end());
  BOOST_REQUIRE(std::find(whateverResult.begin(), whateverResult.end(), ".whatever") != whateverResult.end());
}

BOOST_AUTO_TEST_SUITE_END()
