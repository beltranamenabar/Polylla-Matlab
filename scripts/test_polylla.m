points = rand(10, 2);
tr = delaunayTriangulation(points);

result = Polylla(tr);
disp(result)