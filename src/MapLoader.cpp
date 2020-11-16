/////////////////////////////////////////////
// Filename:        MapLoader.cpp
//
// Description:     MapLoader implementation
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include "MapLoader.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Map.h"

// Change me to true to enable debug message
const bool DEBUG = false;

//////////////////////////////////////////////////////////////////////////////////////
// Continent
//////////////////////////////////////////////////////////////////////////////////////

int Continent::count = 0;

// Default Constructor
/**
 * @brief Construct a new Continent:: Continent object
 *
 */
Continent::Continent()
{
  number = 0;
  name = "";
  value = 0;
  colour = "";
  number_of_territories = 0;
}

// Parameterized constructor
/**
 * @brief Construct a new Continent:: Continent object
 *
 * @param new_name
 * @param new_value
 * @param new_colour
 */
Continent::Continent(std::string new_name, int new_value,
                     std::string new_colour)
{
  number = ++count;
  name = new_name;
  value = new_value;
  colour = new_colour;
  number_of_territories = 0;
}

/**
 * @brief Construct a new Continent:: Continent object
 *
 * @param other_continent
 */
Continent::Continent(const Continent &other_continent)
{
  number = other_continent.number;
  name = other_continent.name;
  value = other_continent.value;
  colour = other_continent.colour;
  number_of_territories = other_continent.number_of_territories;
}

/**
 * @brief Assignment operator overload
 *
 * @param other_continent
 * @return Continent&
 */
Continent &Continent::operator=(const Continent &other_continent)
{
  number = other_continent.number;
  name = other_continent.name;
  value = other_continent.value;
  colour = other_continent.colour;
  number_of_territories = other_continent.number_of_territories;

  return *this;
}

/**
 * @brief Stream insertion operator overload
 *
 * @param output
 * @param continent
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &output, const Continent &continent)
{
  output << "Continent #: " << continent.number << std::endl;
  output << "Name: " << continent.name << std::endl;
  output << "Value: " << continent.value << std::endl;
  output << "Colour: " << continent.colour << std::endl;
  output << "Number of Territories: " << continent.number_of_territories
         << std::endl;

  return output;
}

/**
 * @brief Destroy the Continent:: Continent object
 *
 */
Continent::~Continent()
{
  if (DEBUG)
  {
    std::cout << "Deleting Continent: " << this->name << std::endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// MapFileTerritory
//////////////////////////////////////////////////////////////////////////////////////

// Default Constructor
/**
 * @brief Construct a new MapFileTerritory:: MapFileTerritory object
 *
 */
MapFileTerritory::MapFileTerritory()
{
  number = 0;
  short_name = "";
  continent_number = 0;
  x_coord = 0;
  y_coord = 0;
}

/**
 * @brief Construct a new MapFileTerritory:: MapFileTerritory object
 *
 * @param new_number
 * @param new_short_name
 * @param new_continent_number
 * @param new_x_coord
 * @param new_y_coord
 */
MapFileTerritory::MapFileTerritory(int new_number, std::string new_short_name,
                                   int new_continent_number, int new_x_coord,
                                   int new_y_coord)
{
  number = new_number;
  short_name = new_short_name;
  continent_number = new_continent_number;
  x_coord = new_x_coord;
  y_coord = new_y_coord;
}

// Copy Constructor
/**
 * @brief Construct a new MapFileTerritory:: MapFileTerritory object
 *
 * @param other_territory
 */
MapFileTerritory::MapFileTerritory(const MapFileTerritory &other_territory)
{
  number = other_territory.number;
  short_name = other_territory.short_name;
  continent_number = other_territory.continent_number;
  x_coord = other_territory.x_coord;
  y_coord = other_territory.y_coord;
}

// Assignment Operator
/**
 * @brief
 *
 * @param other_territory
 * @return MapFileTerritory&
 */
MapFileTerritory &MapFileTerritory::operator=(
    const MapFileTerritory &other_territory)
{
  number = other_territory.number;
  short_name = other_territory.short_name;
  continent_number = other_territory.continent_number;
  x_coord = other_territory.x_coord;
  y_coord = other_territory.y_coord;

  return *this;
}

// Stream Insertion Operator
std::ostream &operator<<(std::ostream &output,
                         const MapFileTerritory &territory)
{
  output << "Territory #: " << territory.number << std::endl;
  output << "Short Name: " << territory.short_name << std::endl;
  output << "Continent #: " << territory.continent_number << std::endl;
  output << "Coordinates: ( " << territory.x_coord << " / " << territory.y_coord
         << " )" << std::endl;
  return output;
}

// Default destructor
MapFileTerritory::~MapFileTerritory()
{
  if (DEBUG)
  {
    std::cout << "Deleting MapFileTerritory: " << this->short_name << std::endl;
  }
}

//////////////////////////////////////////////////////////////////////////////////////
// MapFile
//////////////////////////////////////////////////////////////////////////////////////

// Default Constructor
/**
 * @brief Construct a new Map File:: Map File object
 *
 */
MapFile::MapFile()
{
  map_file_name = "";
  pic_file_name = "";
  map_pic_file_name = "";
  cards_file_name = "";
  prv_file_name = "";
}

/**
 * @brief Construct a new Map File:: Map File object
 *
 * @param new_map_file_name
 */
MapFile::MapFile(std::string new_map_file_name)
{
  map_file_name = new_map_file_name;
  pic_file_name = "";
  map_pic_file_name = "";
  cards_file_name = "";
  prv_file_name = "";
}

// Copy Constructor
/**
 * @brief Construct a new Map File:: Map File object
 *
 * @param other_map_file
 */
MapFile::MapFile(const MapFile &other_map_file)
{
  this->map_file_name = other_map_file.map_file_name;
  this->pic_file_name = other_map_file.pic_file_name;
  this->map_pic_file_name = other_map_file.map_pic_file_name;
  this->cards_file_name = other_map_file.cards_file_name;
  this->prv_file_name = other_map_file.prv_file_name;

  for (auto map_continent : other_map_file.map_continents)
    map_continents.push_back(new Continent(*map_continent));
  for (unsigned int i = 0; i < other_map_file.map_territories.size(); i++)
    map_territories.push_back(
        new MapFileTerritory(*(other_map_file.map_territories[i])));
}

// Assignment Operator
/**
 * @brief
 *
 * @param other_map_file
 * @return MapFile&
 */
MapFile &MapFile::operator=(const MapFile &other_map_file)
{
  this->map_file_name = other_map_file.map_file_name;
  this->pic_file_name = other_map_file.pic_file_name;
  this->map_pic_file_name = other_map_file.map_pic_file_name;
  this->cards_file_name = other_map_file.cards_file_name;
  this->prv_file_name = other_map_file.prv_file_name;

  for (unsigned int i = 0; i < other_map_file.map_continents.size(); i++)
    map_continents.push_back(
        new Continent(*(other_map_file.map_continents[i])));
  for (unsigned int i = 0; i < other_map_file.map_territories.size(); i++)
    map_territories.push_back(
        new MapFileTerritory(*(other_map_file.map_territories[i])));

  return *this;
}

// Stream insertion operator
/**
 * @brief Stream insertion operator overload
 *
 * @param output
 * @param map_file
 * @return std::ostream&
 */
std::ostream &operator<<(std::ostream &output, const MapFile *map_file)
{
  output << "Map File: " << map_file->map_file_name
         << "\nPic File: " << map_file->pic_file_name
         << "\nMap Pic File: " << map_file->map_pic_file_name
         << "\nCards File: " << map_file->cards_file_name
         << "\nPreview File: " << map_file->prv_file_name;
  return output;
}

// Destructor
/**
 * @brief Destroy the Map File:: Map File object
 *
 */
MapFile::~MapFile()
{
  // Delete the territories
  for (unsigned int i = 0; i < this->map_territories.size(); i++)
  {
    delete this->map_territories[i];
    this->map_territories[i] = nullptr;
  }

  // Delete the continents
  for (unsigned int i = 0; i < this->map_continents.size(); i++)
  {
    delete this->map_continents[i];
    this->map_continents[i] = nullptr;
  }
}

/**
 * @brief Reads the map file and calls the appropriate function depending on the
 * section its in
 *
 */
Result<void> MapFile::readMapFile()
{
  Result<void> returnResult;
  returnResult.success = false;
  returnResult.message =
      "ERROR: Default failure message. This should not have happened. "
      "MapFile::readMapFile()";

  std::string current_section = "none";
  // Attempt to open the file.
  std::ifstream inputfilestream(map_file_name);
  if (!inputfilestream.is_open())
  {
    returnResult.success = false;
    returnResult.message = "Cound not open map file";
    return returnResult;
  };
  std::string line = "";
  Result<void> result;
  while (std::getline(inputfilestream, line))
  {
    if (!line.empty() && !isStringBlank(line))
    {
      trim(line);
      if (line[0] == ';')
      {
        // Do nothing, this is a commented line
      }
      else if (line[0] == '[')
      {
        std::size_t pos = line.find(']');
        current_section = line.substr(1, pos - 1);
      }
      else
      {
        // Do things according to what section we're in
        if (current_section == "files")
        {
          result = processFileSectionLine(line);
        }
        else if (current_section == "continents")
        {
          result = processContinentSectionLine(line);
        }
        else if (current_section == "countries")
        {
          result = processTerritorySectionLine(line);
        }
        else if (current_section == "borders")
        {
          result = processBordersSectionLine(line);
        }

        // Check the results of processing line
        if (result.success)
        {
          returnResult.success = true;
          returnResult.message = result.message;
          if (DEBUG)
            std::cout << result.message << std::endl;
        }
        else if (!result.success)
        {
          returnResult.success = false;
          returnResult.message = result.message;
          return returnResult;
        }
      }
    }
  }

  // close the file
  inputfilestream.close();

  returnResult.success = true;
  returnResult.message = "DEBUG: Successfully read map file: " + map_file_name;
  return returnResult;
}

/**
 * @brief Processes a line in the file section into the variables in MapFile
 *
 * @param line
 */
Result<void> MapFile::processFileSectionLine(const std::string line)
{
  Result<void> returnResult;
  returnResult.success = false;
  returnResult.message =
      "ERROR: Default failure message. This should not have happened. "
      "MapFile::processFileSectionLine()";

  // Split line into a vector of strings
  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  // Parse line_args and set the appropriate variable
  if (line_args.size() == 2)
  {
    if (toLowerCase(line_args[0]) == "pic")
    {
      pic_file_name = line_args[1];
    }
    else if (toLowerCase(line_args[0]) == "map")
    {
      map_pic_file_name = line_args[1];
    }
    else if (toLowerCase(line_args[0]) == "crd")
    {
      cards_file_name = line_args[1];
    }
    else if (toLowerCase(line_args[0]) == "prv")
    {
      prv_file_name = line_args[1];
    }
    returnResult.success = true;
    returnResult.message =
        "DEBUG: Successfully parsed file section config line: " + line;
  }
  else
  {
    returnResult.success = false;
    returnResult.message = "ERROR: Invalid file section config line: " + line;
  }
  return returnResult;
}

/**
 * @brief Processes a line in the continents section into the map_continents
 * vector
 *
 * @param line
 */
Result<void> MapFile::processContinentSectionLine(const std::string line)
{
  Result<void> returnResult;
  returnResult.success = false;
  returnResult.message =
      "ERROR: Default failure message. This should not have happened. "
      "MapFile::processContinentSectionLine()";

  // Split line into a vector
  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  // Check to ensure the quantity of items on the line is equal to 3.
  // Not equal to 3 is an invalid line in the continents section
  if (line_args.size() == 3)
  {
    int second_arg = 0;
    // try/catch example source:
    // Source:
    // https://codereview.stackexchange.com/questions/206754/an-exception-safe-wrapper-for-stdstoi

    // Is the second arg an int?
    try
    {
      second_arg = std::stoi(line_args[1]);
    }
    catch (const std::invalid_argument &ia)
    {
      returnResult.success = false;
      returnResult.message =
          "ERROR: Invalid argument in continents section: " + line_args[1];
      return returnResult;
    }
    catch (const std::out_of_range &oor)
    {
      returnResult.success = false;
      returnResult.message =
          "ERROR: Invalid argument in continents section: " + line_args[1];
      return returnResult;
    }

    // Create a new continent and add it to the continents list
    Continent *tempContinent;
    tempContinent = new Continent(line_args[0], second_arg, line_args[2]);
    map_continents.push_back(tempContinent);

    returnResult.success = true;
    returnResult.message =
        "DEBUG: Parsed line from continents section: " + line;
  }
  else
  {
    // This was an invalid continents section line
    returnResult.success = false;
    returnResult.message =
        "ERROR: Invalid continent section config line: " + line;
  }
  return returnResult;
}

/**
 * @brief Processes a line in the countries section into the map_territories
 * vector
 *
 * @param line
 */
Result<void> MapFile::processTerritorySectionLine(const std::string line)
{
  Result<void> returnResult;
  returnResult.success = false;
  returnResult.message =
      "ERROR: Default failure message. This should not have happened. "
      "MapFile::processTerritorySectionLine()";

  // Split the string into a vector
  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  // Declare vars to hold the conversions from string to int
  int arg1 = 0;
  int arg3 = 0;
  int arg4 = 0;
  int arg5 = 0;

  // Validate the number of arguments on the line
  if (line_args.size() == 5)
  {
    // try/catch example source:
    // Source:
    // https://codereview.stackexchange.com/questions/206754/an-exception-safe-wrapper-for-stdstoi

    // Attempt to convert the args from string to int
    try
    {
      arg1 = std::stoi(line_args[0]);
      arg3 = std::stoi(line_args[2]);
      arg4 = std::stoi(line_args[3]);
      arg5 = std::stoi(line_args[4]);
    }
    catch (const std::invalid_argument &ia)
    {
      returnResult.success = false;
      returnResult.message =
          "ERROR: Invalid argument in territory section: " + line;
      return returnResult;
    }
    catch (const std::out_of_range &oor)
    {
      returnResult.success = false;
      returnResult.message =
          "ERROR: Invalid argument in territory section: " + line;
      return returnResult;
    }

    // Validate the continent arg
    if (isValidContinentNumber(arg3))
    {
      // Create a territory and add it to the map_territories list
      MapFileTerritory *tempTerritory;
      tempTerritory =
          new MapFileTerritory(arg1, line_args[1], arg3, arg4, arg5);
      map_territories.push_back(tempTerritory);
      returnResult.success = true;
      returnResult.message =
          "DEBUG: Parsed line from territory section: " + line;
    }
    else
    {
      returnResult.success = false;
      returnResult.message =
          "\nERROR: Invalid continent ID in territory line: " + line;
    }
  }
  else
  {
    returnResult.success = false;
    returnResult.message =
        "ERROR: Invalid territory section config line: " + line;
  }
  return returnResult;
}

/**
 * @brief Processes a line in the borders section into the appropriate
 * territory's borders
 *
 * @param line
 */
Result<void> MapFile::processBordersSectionLine(const std::string line)
{
  Result<void> returnResult;
  returnResult.success = false;
  returnResult.message =
      "ERROR: Default failure message. This should not have happened. "
      "MapFile::processBordersSectionLine()";

  // Split line_args into a vector
  std::vector<std::string> line_args;
  line_args = split(line, ' ');

  // Ensure there is more than 1 argument in the list
  if (line_args.size() > 1)
  {
    int arg0 = 0;
    // try/catch example source:
    // Source:
    // https://codereview.stackexchange.com/questions/206754/an-exception-safe-wrapper-for-stdstoi

    // Attempt to convert the first arg
    try
    {
      arg0 = std::stoi(line_args[0]);
    }
    catch (const std::invalid_argument &ia)
    {
      returnResult.success = false;
      returnResult.message =
          "ERROR: Invalid argument in borders section: " + line_args[0];
      return returnResult;
    }
    catch (const std::out_of_range &oor)
    {
      returnResult.success = false;
      returnResult.message =
          "ERROR: Invalid argument in borders section: " + line_args[0];
      return returnResult;
    }

    // Get the territory from arg0
    Result<MapFileTerritory> result;
    result = getTerritoryByNumber(arg0);
    if (result.success)
    {
      // Its a valid territory
      MapFileTerritory *tempTerritory;
      tempTerritory = result.returnValue;
      for (unsigned int i = 1; i < line_args.size(); i++)
      {
        int border_territory_number = 0;
        // try/catch example source:
        // Source:
        // https://codereview.stackexchange.com/questions/206754/an-exception-safe-wrapper-for-stdstoi

        // Attempt to convert the remaining args on the line
        try
        {
          border_territory_number = std::stoi(line_args[i]);
        }
        catch (const std::invalid_argument &ia)
        {
          returnResult.success = false;
          returnResult.message =
              "ERROR: Invalid argument in borders section: " + line_args[i];
          return returnResult;
        }
        catch (const std::out_of_range &oor)
        {
          returnResult.success = false;
          returnResult.message =
              "ERROR: Invalid argument in borders section: " + line_args[i];
          return returnResult;
        }

        // Check to see if its a valid territory
        Result<MapFileTerritory> secondResult;
        secondResult = getTerritoryByNumber(border_territory_number);
        if (secondResult.success)
        {
          // Its valid, so add it to the list of borders
          tempTerritory->borders.push_back(border_territory_number);
          returnResult.success = true;
          returnResult.message = "\nDEBUG: Successfully added border # " +
                                 line_args[i] + " to territory # " +
                                 line_args[0];
        }
        else
        {
          returnResult.success = false;
          returnResult.message =
              result.message +
              "\nERROR: Invalid territory in borders section: " + line;
          return returnResult;
        }
      }
    }
    else
    {
      returnResult.success = false;
      returnResult.message =
          result.message +
          "\nERROR: Invalid territory in borders section: " + line;
    }
  }
  else
  {
    returnResult.success = false;
    returnResult.message =
        "ERROR: Too few arguments on borders section line: " + line;
  }
  return returnResult;
}

/**
 * @brief Returns a territory object based on territory_number
 *
 * @param territory_number
 * @return MapFileTerritory*
 */
Result<MapFileTerritory> MapFile::getTerritoryByNumber(int territory_number)
{
  Result<MapFileTerritory> returnResult;
  returnResult.success = false;
  returnResult.message =
      &"ERROR: No territory found with index number "[territory_number];
  returnResult.returnValue = nullptr;

  for (unsigned int i = 0; i < map_territories.size(); i++)
  {
    if (map_territories[i]->number == territory_number)
    {
      returnResult.success = true;
      returnResult.message = &"SUCCESS: Found territory at index "[i];
      returnResult.returnValue = map_territories[i];
      return returnResult;
    }
  }
  return returnResult;
}

/**
 * @brief Returns a continent object based on continent_number
 *
 * @param continent_number
 * @return Result<Continent>
 */
Result<Continent> MapFile::getContinentByNumber(int continent_number)
{
  Result<Continent> returnResult;
  returnResult.success = false;
  returnResult.message =
      &"ERROR: No continent found with index number "[continent_number];
  returnResult.returnValue = nullptr;

  for (unsigned int i = 0; i < map_continents.size(); i++)
  {
    if (map_territories[i]->number == continent_number)
    {
      returnResult.success = true;
      returnResult.message = &"SUCCESS: Found continent at index "[i];
      returnResult.returnValue = map_continents[i];
      return returnResult;
    }
  }
  return returnResult;
}

/**
 * @brief Checks if territory_number is valid
 *
 * @param territory_number
 * @return true
 * @return false
 */
bool MapFile::isValidTerritoryNumber(int territory_number)
{
  if (map_territories.size() == 0)
    return false;
  for (unsigned int i = 0; i < map_territories.size(); i++)
    if (map_territories[i]->number == territory_number)
      return true;
  return false;
}

/**
 * @brief Checks if continent_number is valid
 *
 * @param continent_number
 * @return true
 * @return false
 */
bool MapFile::isValidContinentNumber(int continent_number)
{
  if (map_continents.size() == 0)
    return false;
  for (unsigned int i = 0; i < map_continents.size(); i++)
    if (map_continents[i]->number == continent_number)
      return true;
  return false;
}

/**
 * @brief Generates the map in conjunction with the Map class
 *
 * @return Map
 */
Map *MapFile::generateMap()
{
  // Create a Map object to return
  //Map returnMap(map_territories.size(), map_file_name);
  Map *returnMap;
  returnMap = new Map(map_territories.size(), map_file_name);

  for (unsigned int i = 0; i < map_continents.size(); i++) {
    struct::ContinentData *newContinent = new ContinentData();
    newContinent->Name = map_continents[i]->name;
    newContinent->ContinentID = map_continents[i]->number;
    newContinent->NumberOfTerritories = map_continents[i]->number_of_territories;
    newContinent->BonusValue = map_continents[i]->value;
    returnMap->AddContinent(newContinent);
  }
  // Loop through all territories and add them to the map
  for (unsigned int i = 0; i < map_territories.size(); i++)
  {
    Result<Continent> firstContinentResult;
    firstContinentResult =
        getContinentByNumber(map_territories[i]->continent_number);

    // TODO Validate firstContinentResult for failure

    // Create the arguments necessary for the Territory constructor
    std::string firstTerrName = map_territories[i]->short_name;
    int firstTerrID = map_territories[i]->number - 1;
    std::string firstTerrContName = firstContinentResult.returnValue->name;

    if (DEBUG)
    {
      std::cout << "Processing Borders for: " << firstTerrName << std::endl;
      std::cout << "-- Borders: ";
    }

    // Create the origin territory
    Territory *firstTerritory;
    firstTerritory = new Territory(firstTerrName, firstTerrID, firstTerrContName, 0.0f, 0.0f);

    // Loop through all borders and add them as an edge from firstTerritory to
    // secondTerritory
    for (unsigned int j = 0; j < map_territories[i]->borders.size(); j++)
    {
      // Get the continent value
      Result<Continent> secondContinentResult;
      secondContinentResult =
          getContinentByNumber(map_territories[i]->continent_number);

      // TODO Validate secondContinentNumber

      // Get the territory represented by the borders[j]
      Result<MapFileTerritory> secondTerritoryResult;
      secondTerritoryResult =
          getTerritoryByNumber(map_territories[i]->borders[j]);

      // TODO Validate secondTerritoryResult

      // Create the arguments necessary for the Territory Constructor
      std::string secondTerrName =
          secondTerritoryResult.returnValue->short_name;
      int secondTerrID = secondTerritoryResult.returnValue->number - 1;
      std::string secondTerrContName = secondContinentResult.returnValue->name;

      // Create the second territory
      Territory *secondTerritory;
      secondTerritory = new Territory(secondTerrName, secondTerrID, secondTerrContName, 0.0f, 0.0f);

      // Add an edge from first to second
      returnMap->AddEdges(*firstTerritory, *secondTerritory);

      if (DEBUG)
      {
        std::cout << secondTerrName << " -- ";
      }
    }
    if (DEBUG)
    {
      std::cout << std::endl;
    }
    // delete firstTerritory;
  }
  return returnMap;
}

/**
 * @brief Validates the MapFile structure
 *
 * @return Result<void>
 */
Result<void> MapFile::validate()
{
  Result<void> returnResult;
  returnResult.success = false;
  returnResult.message =
      "\nERROR: Default failure message. This should not have happened. "
      "MapFile::validate()";

  ///////////////////////////////////////////////////
  // There is at least 1 continent
  //////////////////////////////////////////////////
  if (map_continents.size() == 0)
  {
    returnResult.success = false;
    returnResult.message = "\nERROR: There are no continents!";
    return returnResult;
  }

  ///////////////////////////////////////////////////
  // Each continent contains at least one territory
  ///////////////////////////////////////////////////
  const int arr_size = map_continents.size();
  std::vector<int> continent_array(arr_size);
  // Initialize all elements of the vector to 0
  for (int i = 0; i < arr_size; i++)
  {
    continent_array[i] = 0;
  }
  // Add +1 for each continent
  for (unsigned int i = 0; i < map_territories.size(); i++)
  {
    int j = map_territories[i]->continent_number - 1;
    continent_array[j]++;
  }
  // Loop through continent_array to ensure none are 0
  for (int i = 0; i < arr_size; i++)
  {
    if (continent_array[i] == 0)
    {
      returnResult.success = false;
      returnResult.message = "\nERROR: Continent # " + std::to_string(i + 1) +
                             " does not have any territories.";
      return returnResult;
    }
  }

  /////////////////////////////////////////////////////
  // There is at least 1 territory
  ////////////////////////////////////////////////////
  if (map_territories.size() == 0)
  {
    returnResult.success = false;
    returnResult.message = "\nERROR: There are no territories!";
    return returnResult;
  }

  /////////////////////////////////////////////////////////
  // There are borders on at least 1 territory
  ////////////////////////////////////////////////////////
  bool borderFound = false;
  for (unsigned int i = 0; i < map_territories.size(); i++)
  {
    if (map_territories[i]->borders.size() != 0)
    {
      borderFound = true;
      break;
    }
  }
  if (!borderFound)
  {
    returnResult.success = false;
    returnResult.message = "\nERROR: Territories do not have any borders.";
    return returnResult;
  }

  returnResult.success = true;
  returnResult.message = "\nDEBUG: All mapfile validation tests passed.";
  return returnResult;
}

/////////////////////////////////////////////////////////////////////////////////
//
// Miscellaneous String helper Functions
//
/////////////////////////////////////////////////////////////////////////////////

std::string toLowerCase(const std::string toLower)
{
  std::string lowerCase = "";
  if (toLower.empty())
    return toLower;
  for (unsigned int i = 0; i < toLower.length(); i++)
  {
    lowerCase += tolower(toLower[i]);
  }
  return lowerCase;
}

//////////////////
// Source:
// https://www.toptip.ca/2010/03/trim-leading-or-trailing-white-spaces.html
void trim(std::string &s)
{
  size_t p = s.find_first_not_of("\t\n\v\f\r ");
  s.erase(0, p);

  p = s.find_last_not_of("\t\n\v\f\r ");
  if (std::string::npos != p)
    s.erase(p + 1);
}
/////////////////

// Returns false if no non-space characters are found
// Returns true otherwise
bool isStringBlank(const std::string line)
{
  if (!line.empty())
  {
    for (unsigned int i = 0; i < line.length(); i++)
    {
      // Source: https://en.cppreference.com/w/cpp/string/byte/isspace
      if (!std::isspace(static_cast<unsigned char>(line[i])))
      {
        return false;
      }
    }
  }
  return true;
}

///////////////////
// Source: https://thispointer.com/how-to-split-a-string-in-c/
std::vector<std::string> split(std::string strToSplit, char delimiter)
{
  std::stringstream ss(strToSplit);
  std::string item;
  std::vector<std::string> splittedStrings;
  while (std::getline(ss, item, delimiter))
  {
    splittedStrings.push_back(item);
  }
  return splittedStrings;
}
///////////////////
