
#include "var_spec.h"
#include "standard_var_spec.h"

#include<limits>
#include<cmath>

namespace depnet
{
    StandardVariableSpecification::StandardVariableSpecification() : 
        isBool(false), isOrd(false), isDisc(false), 
        minVal(std::numeric_limits<double>::max()), 
        maxVal(std::numeric_limits<double>::max()) { }

    StandardVariableSpecification::~StandardVariableSpecification() { }

    std::string StandardVariableSpecification::getName() const
    {
        return this->name;
    }

    void StandardVariableSpecification::setName(std::string name)
    {
        this->name = name;
    }

    bool StandardVariableSpecification::hasRange() const
    {
        return !std::isinf(minVal) || !std::isinf(maxVal);
    }

    void StandardVariableSpecification::getRange(double& minVal, double& maxVal) const
    {
        minVal = this->minVal;
        maxVal = this->maxVal;
    }

    void StandardVariableSpecification::setRange(double minVal, double maxVal)
    {
        this->minVal = minVal;
        this->maxVal = maxVal;
    }

    bool StandardVariableSpecification::isDiscrete() const
    {
        return this->isDisc;
    }

    void StandardVariableSpecification::setDiscrete(bool isDiscrete)
    {
        this->isDisc = isDiscrete;
    }

    bool StandardVariableSpecification::isOrdinal() const
    {
        return this->isOrd;
    }

    void StandardVariableSpecification::setOrdinal(bool isOrdinal)
    {
        this->isOrd = isOrdinal;
    }

    bool StandardVariableSpecification::isBoolean() const
    {
        return this->isBool;
    }

    void StandardVariableSpecification::setBoolean(bool isBoolean)
    {
        this->isBool = isBoolean;
    }

    const std::map<int, std::string> StandardVariableSpecification::getLevelMap() const
    {
        std::map<int, std::string> levelMap;
        int levelNum = 0;
        for(auto levelIt = levels.begin(); levelIt != levels.end(); ++levelIt)
            levelMap.insert(std::pair<int, std::string>(levelNum, *levelIt));
        return levelMap;
    }

    const std::vector<std::string>& StandardVariableSpecification::getLevels() const
    {
        return this->levels;
    }

    const int StandardVariableSpecification::getNumLevels() const
    {
        return this->levels.size();
    }

    void StandardVariableSpecification::setLevels(std::vector<std::string> levels)
    {
        this->levels = std::move(levels);
    }
}

