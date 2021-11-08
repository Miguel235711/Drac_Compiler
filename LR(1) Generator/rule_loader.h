#ifndef RULE_LOADER_H
#define RULE_LOADER_H

#include <string>

#include "production_rule.h"

class RuleLoader{
    public:
        static std::vector<ProductionRule *> load_rules(std::string in_file_name);
};

#endif // RULE_LOADER_H