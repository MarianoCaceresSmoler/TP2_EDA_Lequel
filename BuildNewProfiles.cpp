#include "BuildNewProfiles.h"
#include "Text.h"
#include "CSVData.h"
#include "Lequel.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>

/**
 * @brief Creates a trigram profile from a text file and saves it as a CSV.
 * 
 * @param path Path to the input text file (corpus for a new language).
 * @param CSVpath Path where the resulting CSV file will be written.
 */
void createLanguage(std::string path, std::string CSVpath){

    Text corpus;

    // Load the text from file into the corpus and buld its trigram profile
    getTextFromFile(path, corpus);
    TrigramProfile newTrigramProfile = buildTrigramProfile(corpus);

    // Convert trigram profile into CSV format
    // Each entry: trigram, frequency
    CSVData csv;
    for (const auto &p : newTrigramProfile) {
        csv.push_back({p.first, std::to_string(p.second)});
    }

    // Write the CSV file to disk
    if (!writeCSV(CSVpath, csv)) {
        std::cerr << "Error al escribir CSV en " << CSVpath << std::endl;
    } else {
        std::cout << "CSV escrito correctamente en " << CSVpath << std::endl;
    }

    std::cout << "Generando CSV con " << newTrigramProfile.size() << " trigramas" << std::endl;

}
