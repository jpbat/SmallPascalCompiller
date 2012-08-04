program cenas;
var x : array [0..2] of integer;

function a() : integer;
begin
	x[0] := x[0]+1;
	a := x[0];
end;

begin
	x[0] := 10;
	writeln(x[0]);
	writeln(a());
	writeln(x[0]);
end.