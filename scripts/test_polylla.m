points = rand(10, 2);
tr = delaunayTriangulation(points);
io = isInterior(tr);
dt = tr(io,:);
tri = triangulation(dt, points);
trimesh(tri.ConnectivityList, tri.Points(:, 1), tri.Points(:, 2))


p = Polylla(tri);

%% Convert to polyshape to show
num_poly = size(p.polygons);
new_poly = polyshape.empty(0, num_poly(1));
for i=1:num_poly(1)
    polygon_size = size(p.polygons{i});
    x = zeros(polygon_size(1), 1);
    y = zeros(polygon_size(1), 1);
    for j=1:polygon_size(1)
        x(j) = p.points(p.polygons{i}(j), 1);
        y(j) = p.points(p.polygons{i}(j), 2);
    end
    new_poly(i) = polyshape(x, y);
end

plot(new_poly)