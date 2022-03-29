#ifndef CRAWLER_DICTIONARY_HPP
#define CRAWLER_DICTIONARY_HPP

// for dictionaries (key-value-pairing)
#include <map>
#include <string>

class Dictionary {
public:
    Dictionary();
    std::string getSkillName(int index);
    std::string getItemName(int index);
    std::string getMessageSnippet(int index);

private:
    std::map<int, std::string> skillNames;
    std::map<int, std::string> itemNames;
    std::map<int, std::string> mesSnippets;
};


#endif //CRAWLER_DICTIONARY_HPP
