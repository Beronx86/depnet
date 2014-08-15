
#pragma once

#ifndef GIBBS_ITERATOR_H
#define GIBBS_ITERATOR_H

#include <boost/iterator/iterator_facade.hpp>
#include <vector>
#include "gibbs_sampler.h"

namespace depnet 
{
    typedef std::shared_ptr<std::map<std::shared_ptr<VariableSpecification>, double> > SampleType;

    /**
     * An forward-traversal iterator over samples produced by Gibbs sampling
     */
    class GibbsIterator
    {
    public:
       virtual SampleType const operator++() = 0;
       virtual SampleType const operator++(int) = 0;
       virtual SampleType const operator*() const = 0;
    private:
       virtual SampleType const dereference() const = 0;
    };

}

#endif



