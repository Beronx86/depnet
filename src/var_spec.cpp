
#include "var_spec.h"

#include<limits>
#include<cmath>

namespace depnet
{
    VariableSpecification::VariableSpecification() : 
        isBool(false), isOrd(false), isDisc(false), 
        minVal(std::numeric_limits<double>::max()), 
        maxVal(std::numeric_limits<double>::max()) { }

    VariableSpecification::~VariableSpecification() { }

    std::string VariableSpecification::getName() const
    {
        return this->name;
    }

    void VariableSpecification::setName(std::string name)
    {
        this->name = name;
    }

    bool VariableSpecification::hasRange() const
    {
        return !std::isinf(minVal) || !std::isinf(maxVal);
    }

    void VariableSpecification::getRange(double& minVal, double& maxVal) const
    {
        minVal = this->minVal;
        maxVal = this->maxVal;
    }

    void VariableSpecification::setRange(double minVal, double maxVal)
    {
        this->minVal = minVal;
        this->maxVal = maxVal;
    }

    bool VariableSpecification::isDiscrete() const
    {
        return this->isDisc;
    }

    void VariableSpecification::setDiscrete(bool isDiscrete)
    {
        this->isDisc = isDiscrete;
    }

    bool VariableSpecification::isOrdinal() const
    {
        return this->isOrd;
    }

    void VariableSpecification::setOrdinal(bool isOrdinal)
    {
        this->isOrd = isOrdinal;
    }

    bool VariableSpecification::isBoolean() const
    {
        return this->isBool;
    }

    void VariableSpecification::setBoolean(bool isBoolean)
    {
        this->isBool = isBoolean;
    }

    const std::map<int, std::string> VariableSpecification::getLevelMap() const
    {
        std::map<int, std::string> levelMap;
        int levelNum = 0;
        for(auto levelIt = levels.begin(); levelIt != levels.end(); ++levelIt)
            levelMap.insert(std::pair<int, std::string>(levelNum, *levelIt));
        return levelMap;
    }

    const std::vector<std::string>& VariableSpecification::getLevels() const
    {
        return this->levels;
    }

    const int VariableSpecification::getNumLevels() const
    {
        return this->levels.size();
    }

    void VariableSpecification::setLevels(std::vector<std::string> levels)
    {
        this->levels = std::move(levels);
    }
}

