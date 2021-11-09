#ifndef RULES_DRIVER_H
#define RULES_DRIVER_H

#include <vector>

#include "LR(1) Generator\\rule_loader.h"
#include "LR(1) Generator\\production_rule.h"


class RulesDriver{
    public:
        
        RulesDriver(std::string in_file_name);
        ~RulesDriver();

        //TODO: define methods for syntactical stack ...    

        ProductionRule * get_rule(int rule_number);

    private:

        std::vector<ProductionRule*> rules;
};

#endif // RULES_DRIVER_H