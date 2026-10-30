
module regular_polygon(order=5, r=10){
     angles=[ for (i = [0:order-1]) i*(360/order) ];
     coords=[ for (th=angles) [r*cos(th), r*sin(th)] ];
     polygon(coords);
 }

rotate(a = [0, 90, 15])
difference()
{
    linear_extrude(height = 300, center = false, convexity = 10, twist = 180, slices = 50, scale = 0.4, $fn = 50)
    {
        regular_polygon();
    }
    // Magnet hole
    translate(v = [0, 0, 300 - 6.35 + 0.01])
        #cylinder(r = 1.6, h = 6.35, $fn = 50);
    // Tag hole
    rotate(a = [0, 0, 30])
        translate(v = [-25, 0, 10])
            rotate(a = [0, 90, 0])
                cylinder(r = 3, h = 50, $fn = 50);
}
