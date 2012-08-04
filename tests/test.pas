program for2;
function a ():  integer;
var i : integer;
begin	
	for i := 2 to 5 do
		writeln(i);
	a := i;
end;

begin
	writeln(a());
end.
