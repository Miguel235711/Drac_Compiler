#include "rules_driver.h"


RulesDriver::RulesDriver(std::string in_file_name):rules(RuleLoader::load_rules(in_file_name)){
}
RulesDriver::~RulesDriver(){

}

ProductionRule * RulesDriver::get_rule(int rule_number){
    assert(rule_number<rules.size());
    return rules[rule_number];
}