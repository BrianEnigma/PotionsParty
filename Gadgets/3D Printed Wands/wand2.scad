include <BOSL2/std.scad>

rotate(a = [0, 90, 15])
difference()
{
    linear_extrude(height = 300, center = false, convexity = 10, twist = 180, slices = 50, scale = 0.3, $fn = 100)
    {
        regular_ngon(n=5, r=10, rounding=2, $fn=100);
    }
    // Magnet hole
    translate(v = [0, 0, 300 - 6.35 + 0.01])
        #cylinder(r = 1.7, h = 6.35, $fn = 50);
    // Tag hole
    rotate(a = [0, 0, 30])
        translate(v = [-25, 0, 10])
            rotate(a = [0, 90, 0])
                cylinder(r = 3, h = 50, $fn = 50);
}
