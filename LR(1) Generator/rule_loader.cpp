#include "rule_loader.h"

std::vector<ProductionRule *> RuleLoader::load_rules(std::string in_file_name){
    std::ifstream in(in_file_name.c_str());
    std::string line;
    int symbol, rule_count = 0;
    std::vector<ProductionRule*> rules;
    while(getline(in,line)){
        //std::cout << "line: " << line << "\n";
        std::stringstream line_stream(line);
        line_stream >> symbol;
        //std:: cout << "left non-terminal: " << symbol << "\n";
        ProductionRule * rule = new ProductionRule(rule_count++,symbol);
        while(line_stream >> symbol){
            //std::cout << "right symbol: " << symbol << "\n";
            rule->add_right_symbol(symbol);
        }
        //std::cout << "what: " << rule.get_first_right_symbol() << "\n";
        rules.push_back(rule);
    }
    return rules;
}