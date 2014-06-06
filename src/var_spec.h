
#pragma once

#ifndef VARIABLE_SPECIFICATION_H
#define VARIABLE_SPECIFICATION_H

namespace depnet {

    /**
     * Contains metadata about a variable
     */
    class VariableSpecification {
    public:

        /**
         * Creates a new container for variable metadata
         */
        VariableSpecification();

        /**
         * Destroys the variable metadata
         */
        ~VariableSpecification();

        /**
         * Retrieves the name of this variable
         * @return The name/label of the variable
         */ 
        std::string getName();

        /**
         * Establishes or overwrites this variable's name.
         * This name is primarily useful when presenting data to the end user.
         * @param name The name of the variable to store
         */
        void setName(std::string name);

        /**
         * Indicates if this variable is range-restricted.
         * This will only be true if setRange has been called with non-inf values.
         * @see setRange
         */
        bool hasRange() const; 

        /**
         * Retrieves the minimum and maximum values 
         * @param minVal The smallest value allowed for the variable
         * @param maxVal The largest value allowed for the variable
         */
        void getRange(double& minVal, double& maxVal) const;

        /**
         * Establishes a restricted range for the variable
         * @param minVal The smallest allowable value of the variable
         * @param maxVal The largest allowable value of the variable
         */
        void setRange(double minVal, double maxVal);

        /**
         * Indicates if this metadata represents a discrete variable
         * @return Returns true if this variable has been 
         * configured as discrete, false otherwise
         */
        bool isDiscrete() const;

        /**
         * Marks this variable as discrete or continuous. Ensure that ::setLevels has been called to 
         * establish the names of the discrete variables when marking as discrete.
         * @param isDiscrete Indicates if this variable is discrete
         */
        void setDiscrete(bool isDiscrete);

        /**
         * Indicates if this is an ordinal variable
         * @return True if this variable has been configured as ordinal, false otherwise
         */
        bool isOrdinal() const;

        /**
         * Marks this variable as ordinal or non-ordinal (i.e. strictly discrete or continuous).
         * @param isOrdinal Indicates if this is an ordinal variable. 
         * When true, this variable will also be marked as discrete.
         */
        void setOrdinal(bool isOrdinal);

        /**
         * Gets a value indicating if this variable 
         * is configured as a Boolean
         * @return Returns true if this variable has been 
         * configured as Boolean, false otherwise
         */
        bool isBoolean() const;

        /**
         * Sets a value indicating if this is a Boolean variable
         * @param isBoolean Indicates if this variable 
         * should be configured as Boolean
         */
        void setBoolean(bool isBoolean);

        /**
         * Builds a map from factor level as an integer to a level as a name.
         * @return A mapping from a positive integer factor ID to the 
         * name of the level of that factor.
         */
        std::map<int, std::string> getLevelMap() const;

        /**
         * Retrieves the names of the levels for a discrete variable
         * @return The names of the levels as a string, 
         * or an empty vector if this is not a discrete variable
         */
        std::vector<std::string> getLevels() const;

        /**
         * Stores the names of the levels of this variable.
         * Calling this method will set this variable as discrete.
         * If the levels represent ordinal values, they should be 
         * supplied in order and ::setOrdinal should be called.
         * @param levels The names of the levels as strings
         */
        void setLevels(std::vector<std::string> levels);
    private:    

        /** The name/label of the variable */
        std::string name;

        /** The minimum value of the restricted range */
        double minVal;

        /** The maximum value of the restricted range */
        double maxVal;

        /** Indicates if this is a boolean variable */
        bool isBoolean;

        /** Indicates if this is an ordinal variable */
        bool isOrdinal;

        /** Indicates if this is a discrete variable */
        bool isDiscrete;

        /** Names of variable values for a discrete variable */
        std::vector<std::string> levels;
    };

}

#endif

