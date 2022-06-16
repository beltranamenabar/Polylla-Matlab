classdef Polylla
    %Polylla A Matlab wrapper for the Polylla C++ Algorithm

    properties
        points
        triangles
        neighs
        triangulation
        polygons
        metrics
    end

    methods
        function obj = Polylla(points, tri, neighs)
            %Polylla Construct an instance of this class

            if nargin == 1
                if isa(points, 'triangulation')
                    % Triangulation
                    obj.triangulation = points
                    obj.points = obj.triangulation.Points;
                    obj.triangles = obj.triangulation.ConnectivityList;
                    obj.neighs = obj.triangulation.neighbors;
                elseif ismatrix(points)
                    % Points
                    obj.points = points;
                    obj.triangulation = delaunayTriangulation(obj.points);
                    obj.triangles = obj.triangulation.ConnectivityList;
                    obj.neighs = obj.triangulation.neighbors;
                else
                    error('Polylla:InvalidInput', 'Invalid input');
                end

            elseif nargin == 2
                % points and triangles
                obj.points = points;
                obj.triangles = tri;
                obj.triangulation = triangulation(obj.triangles, obj.points);
                obj.neighs = obj.triangulation.neighbors;

            elseif nargin == 3
                % points, triangles and neighbors
                obj.points = points;
                obj.triangles = tri;
                obj.neighs = neighs;
                obj.triangulation = triangulation(obj.triangles, obj.points);
            else
                error('Polylla:InvalidInput', 'Invalid input');
            end

            obj = obj.useCPPPolylla();

        end
    end

    methods (Access = private)
        obj = useCPPPolylla(obj)
    end
end