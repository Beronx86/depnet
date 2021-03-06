
#pragma once

#ifndef VARIABLE_SPECIFICATION_H
#define VARIABLE_SPECIFICATION_H

#include<string>
#include<vector>
#include<map>

namespace depnet {

    /**
     * Contains metadata about a variable which is used to determine how best 
     * the variable should be encoded and used for training.
     */
    class VariableSpecification 
    {
    public:
        /**
         * Retrieves the name of this variable
         * @return The name/label of the variable
         */ 
        virtual std::string getName() const = 0;

        /**
         * Establishes or overwrites this variable's name.
         * This name is primarily useful when presenting data to the end user.
         * @param name The name of the variable to store
         */
        virtual void setName(std::string name) = 0;

        /**
         * Indicates if this variable is range-restricted.
         * This will only be true if setRange has been called with non-inf values.
         * @see setRange
         */
        virtual bool hasRange() const = 0; 

        /**
         * Retrieves the minimum and maximum values 
         * @param minVal The smallest value allowed for the variable
         * @param maxVal The largest value allowed for the variable
         */
        virtual void getRange(double& minVal, double& maxVal) const = 0;

        /**
         * Establishes a restricted range for the variable
         * @param minVal The smallest allowable value of the variable
         * @param maxVal The largest allowable value of the variable
         */
        virtual void setRange(double minVal, double maxVal) = 0;

        /**
         * Indicates if this metadata represents a discrete variable
         * @return Returns true if this variable has been 
         * configured as discrete, false otherwise
         */
        virtual bool isDiscrete() const = 0;

        /**
         * Marks this variable as discrete or continuous. Ensure that StandardVariableSpecification::setLevels has been called to 
         * establish the names of the discrete variables when marking as discrete.
         * @param isDiscrete Indicates if this variable is discrete
         */
        virtual void setDiscrete(bool isDiscrete) = 0;

        /**
         * Indicates if this is an ordinal variable (e.g. with ordered levels 1-10, 10-20, 20-30).
         * @return True if this variable has been configured as ordinal, false otherwise
         */
        virtual bool isOrdinal() const = 0;

        /**
         * Marks this variable as ordinal or non-ordinal (i.e. strictly discrete or continuous).
         * @param isOrdinal Indicates if this is an ordinal variable. 
         * When true, this variable will also be marked as discrete.
         */
        virtual void setOrdinal(bool isOrdinal) = 0;

        /**
         * Gets a value indicating if this variable 
         * is configured as a Boolean indicator.
         * @return Returns true if this variable has been 
         * configured as Boolean, false otherwise
         */
        virtual bool isBoolean() const = 0;

        /**
         * Sets a value indicating if this is a Boolean variable
         * @param isBoolean Indicates if this variable 
         * should be configured as Boolean
         */
        virtual void setBoolean(bool isBoolean) = 0;

        /**
         * Builds a map from factor level as an integer to a level as a name.
         * @return A mapping from a positive integer factor ID to the 
         * name of the level of that factor.
         */
        virtual const std::map<int, std::string> getLevelMap() const = 0;

        /**
         * Retrieves the names of the levels for a discrete variable
         * @return The names of the levels as a string, 
         * or an empty vector if this is not a discrete variable
         */
        virtual const std::vector<std::string>& getLevels() const = 0;

        /**
         * Retrieves the number of levels established for this discrete variable
         * @return The names of variable levels as a string
         */
        virtual const int getNumLevels() const = 0;

        /**
         * Stores the names of the levels of this variable.
         * Calling this method will set this variable as discrete.
         * If the levels represent ordinal values, they should be 
         * supplied in order and StandardVariableSpecification::setOrdinal should be called.
         * @param levels The names of the levels as strings
         */
        virtual void setLevels(std::vector<std::string> levels) = 0;
    };

}

#endif

