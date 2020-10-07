MAGNET_DIAMETER = 10;
MAGNET_LENGTH = 9.5;
MAGNET_DEPTH = MAGNET_LENGTH - 2;
MAGNET_CYLINDER_THICKNESS = 2;
RING_INNER_DIAMETER = 20;
DETAIL = 100;

module magnetHole()
{
	translate(v = [0, 0, MAGNET_CYLINDER_THICKNESS])
		cylinder(r = MAGNET_DIAMETER/2, h = MAGNET_LENGTH, $fn = DETAIL);
}

module holder()
{
	intersection()
	{
		difference()
		{
			cylinder(r = MAGNET_DIAMETER/2 + MAGNET_CYLINDER_THICKNESS, h = MAGNET_DEPTH, $fn = DETAIL);
			magnetHole();
		}
		cylinder(r1 = 1.5 * (MAGNET_DIAMETER/2 + MAGNET_CYLINDER_THICKNESS), r2=0, h = 2 * MAGNET_DEPTH, $fn = DETAIL);
	}
}

module ring()
{
	translate(v = [0, 0, RING_INNER_DIAMETER / -2])
		rotate(a = [90, 0, 0])
			rotate_extrude(convexity = 10, $fn = DETAIL)
				translate([RING_INNER_DIAMETER / 2 + 5 * 0.5, 0, 0])
					scale(v = [0.5, 1, 1])
						circle(r = 5, $fn = DETAIL);	
}

difference()
{
	union()
	{
		holder();
		ring();
	}
	magnetHole();
}
