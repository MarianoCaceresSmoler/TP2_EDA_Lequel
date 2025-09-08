/**
 * @brief Reads and writes CSV files
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 *
 * @cite https://towardsdatascience.com/understanding-cosine-similarity-and-its-application-fd42f585296a
 */

#ifndef CSVDATA_H
#define CSVDATA_H

#include <string>
#include <vector>

// CSVData: vector of vector of fields
typedef std::vector<std::vector<std::string>> CSVData;

bool readCSV(const std::string path, CSVData &data);
bool writeCSV(const std::string path, CSVData &data);

#endif
