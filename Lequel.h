/**
 * @brief Lequel? language identification based on trigrams
 * @author Marc S. Ressl
 *
 * @copyright Copyright (c) 2022-2023
 *
 * @cite https://towardsdatascience.com/understanding-cosine-similarity-and-its-application-fd42f585296a
 */

#ifndef LEQUEL_H
#define LEQUEL_H

#include <list>
#include <unordered_map>
#include <string>

#include "Text.h"

// TrigramProfile: map of trigram -> frequency
typedef std::unordered_map<std::string, float> TrigramProfile;

// TrigramList: list of trigrams
typedef std::list<std::string> TrigramList;

struct LanguageProfile
{
    std::string languageCode;
    TrigramProfile trigramProfile;
};

typedef std::vector<LanguageProfile> LanguageProfiles;

// Functions
TrigramProfile buildTrigramProfile(const Text &text);
void normalizeTrigramProfile(TrigramProfile &trigramProfile);
float getCosineSimilarity(TrigramProfile &textProfile, TrigramProfile &languageProfile);
std::string identifyLanguage(const Text &text, LanguageProfiles &languages);
std::string identifyLanguageThreads(const Text &text, LanguageProfiles &languages);

#endif
