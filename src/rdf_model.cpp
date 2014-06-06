

explicit RandomForestModel::RandomForestModel(
        std::vector<std::shared_ptr<VariableSpecification> > indep, 
        std::shared_ptr<VariableSpecification> dep) : independentVars(indep), dependentVar(dep)
{
}

~RandomForestModel::RandomForestModel() { }

double RandomForestModel::predict(std::vector<double> indep)
{

}

void RandomForestModel::train(boost::multi_array<double, 2> indep, std::vector<double> dep)
{

}


