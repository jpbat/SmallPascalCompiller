program testStatement;

var a : integer;
	b : real;
	c : boolean;
	d : array [0..3] of integer;
	e : array [0..3] of real;
	f : array [0..3] of boolean;

begin
	
	(* assign statements *)
	a := 0;
	b := 1.1;
	c := true;
	d[0] := 3;
	e[1] := 4.5;
	f[2] := false;

	writeln(a);
	writeln(b);
	writeln(c);
	writeln(d[0]);
	writeln(e[1]);
	writeln(f[2]);

	(* if statement *)

	if true then
		writeln(5);

	if false then
		writeln(4)
	else
		writeln(5);

	(* while statement *)

	while a > 10 do
	begin
		writeln(a);
		a := a+1;
	end;

	(* valparamstr statement e writeln *)
	val(paramstr(0), a);
	writeln(a);

end.
