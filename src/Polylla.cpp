#include "mex.hpp"
#include "mexAdapter.hpp"

class MexFunction : public matlab::mex::Function {

public:

    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {

        checkArguments(outputs, inputs);

        outputs[0] = std::move(inputs[0]);
    }

private:

    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    matlab::data::ArrayFactory factory;

    void checkArguments(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {

        if(inputs.size() != 1) {
            matlabPtr->feval(
            u"error", 0, std::vector<matlab::data::Array>({factory.createScalar("Polylla just works with a single input")})
            );
        }

        if(inputs[0].getNumberOfElements() != 1) {
            matlabPtr->feval(
            u"error", 0, std::vector<matlab::data::Array>({factory.createScalar("Polylla just works with a single input")})
            );
        }

        /* Check if the parameter is a triangulation
        if(inputs[0].getType() != matlab::data::) {
            matlabPtr
            ->feval(u"error", 0, std::vector<matlab::data::Array>({factory.createScalar("Input must be a triangulation")}));
        }
        */
    }
};