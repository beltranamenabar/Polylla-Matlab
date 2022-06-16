#include <string>
#include <vector>

#include "mex.hpp"
#include "mexAdapter.hpp"

#include <polylla.hpp>
#include <triangulation.hpp>
#include <vertex.hpp>


class MexFunction : public matlab::mex::Function {

public:

    void operator()(matlab::mex::ArgumentList outputs, matlab::mex::ArgumentList inputs) {

        checkArguments(inputs);

        matlab::data::Array polylla = inputs[0];

        matlab::data::Array points = matlabPtr->getProperty(polylla, "points");
        matlab::data::Array connectivity_list = matlabPtr->getProperty(polylla, "triangles");

        matlab::data::ArrayDimensions dims = points.getDimensions();
        int n_points = dims[0];


        std::vector<Vertex> vertices(n_points);
        for(int i = 0; i < n_points; ++i) {
            vertices[i].x = static_cast<double>(points[i][0]);
            vertices[i].y = static_cast<double>(points[i][1]);
        }


        std::vector<int> triangles(3 * connectivity_list.getDimensions()[0]);
        for(int i = 0; i < connectivity_list.getDimensions()[0]; i++) {
            for(int j = 0; j < 3; ++j) {
                triangles[3 * i + j] = static_cast<int>(connectivity_list[i][j]) - 1;
            }
        }


        Triangulation tr(vertices, triangles); // Error acá
        Polylla mesh(std::move(tr));
        mesh.construct_polylla();
        std::vector<Polygon> polygons = mesh.get_polygonal_mesh();


        std::size_t n_polygons = polygons.size();
        matlab::data::CellArray polygons_output = factory.createCellArray({n_polygons, 1});

        for(int i = 0; i < n_polygons; ++i) {
            displayOnMATLAB("Polygon " + std::to_string(i) + " ");
            auto polygon = factory.createArray<int>({polygons[i].vertices.size(), 1});
            for(int j = 0; j < polygons[i].vertices.size(); ++j) {
                displayOnMATLAB(std::to_string(polygons[i].vertices[j]) + " ");
                polygon[j] = (polygons[i].vertices[j]) + 1;
            }
            polygons_output[i] = polygon;
            displayOnMATLAB("\n");
        }

        matlabPtr->setProperty(polylla, "polygons", polygons_output);

        outputs[0] = std::move(polylla);
    }

private:

    std::shared_ptr<matlab::engine::MATLABEngine> matlabPtr = getEngine();
    matlab::data::ArrayFactory factory;

    /**
     * @brief Checks if the inputs are valid
     *
     * @param inputs A list of inputs
     */
    void checkArguments(matlab::mex::ArgumentList inputs) {

        if(inputs.size() != 1) {
            printError("Polylla just works with a single input");
        }

        // Check if the input is a Polylla object with isa('Polylla')
        matlab::data::Array input = inputs[0];
        std::vector<matlab::data::Array> isa_args{input, factory.createScalar("Polylla")};
        matlab::data::TypedArray<bool> isa_check = matlabPtr->feval(u"isa", isa_args);
        if(!isa_check[0]) {
            printError("Polylla wrapper just works with a Polylla object");
        }
    }

    /**
     * @brief Prints an error message to the MATLAB console
     *
     * @param error A string with the message to print
     */
    void printError(std::string error) {
        matlabPtr->feval(u"error", 0, std::vector<matlab::data::Array>({factory.createScalar(error)}));
    }

    void displayOnMATLAB(std::string text) {
        // Pass stream content to MATLAB fprintf function
        matlabPtr->feval(u"fprintf", 0, std::vector<matlab::data::Array>({factory.createScalar(text)}));
    }
};