#pragma once

using ItemID = int64_t;
using BodyID = int64_t;
using PolyID = int64_t;

constexpr int64_t INVALID_ID = -1;
constexpr int64_t INVALID_INDEX = -1;

const std::string INVALID_PATH = "invalid path";
const std::string INVALID_NAME = "invalid name";
const std::string DEFAULT_ERROR_MESSAGE = "AOK";

using PathList = std::vector<std::filesystem::path>;
