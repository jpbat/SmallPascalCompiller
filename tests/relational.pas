program testRelational;

var c, d: integer;

begin
	
	c := 4;
	d := 5;

	if (d > c) then
		writeln(1);

	if (d >= d) then
		writeln(2);

	if (c < d) then
		writeln(3);

	if (c <= c) then
		writeln(4);

	if (c <> d) then
		writeln(5);

	if (d = d) then
		writeln(6);
end.
