#include "build_new_profiles.h"
#include "Text.h"
#include "CSVData.h"
#include "Lequel.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <cctype>


void create_corpus (std::string path, std::string CSVpath){
    Text corpus;

    getTextFromFile(path, corpus);

    TrigramProfile newTrigramProfile = buildTrigramProfile(corpus);

    CSVData csv;
    for (const auto &p : newTrigramProfile) {
        csv.push_back({p.first, std::to_string(p.second)});
    }

    if (!writeCSV(CSVpath, csv)) {
        std::cerr << "Error al escribir CSV en " << CSVpath << std::endl;
    } else {
        std::cout << "CSV escrito correctamente en " << CSVpath << std::endl;
    }

    std::cout << "Generando CSV con " << newTrigramProfile.size() << " trigramas" << std::endl;

}
