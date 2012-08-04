program functions;

var v : array [0..2] of integer;
	w : array [0..2] of real;
	y : array [0..2] of boolean;
	aa : integer;
	bb : real;
	cc : boolean;

function a() : integer;
begin
	a := 5;
end;

function b() : real;
begin
	b := 6.5;
end;

function c() : boolean;
begin
	c := true;
end;

function d( v1 : integer) : integer;
var x : integer;
begin
	if v1 < 6 then
		x := d(v1+1);
	writeln(v1);
end;

function e( v1 : real) : real;
var x : real;
begin
	if v1 < 1 then
		x := e(v1+0.1);
	writeln(v1);
end;

function f( v1 : integer) : boolean;
var x : boolean;
begin
	if v1 < 6 then
		x := f(v1+1);
	if v1 mod 2 = 0 then
		writeln(1)
	else
		writeln(0);
end;

function g( var v1 : array of integer) : integer;
begin
	g := v1[1];
end;

function h( var v1 : array of real) : real;
begin
	h := v1[1];
end;

function i( var v1 : array of boolean) : boolean;
begin
	i := v1[1];
end;

function j( var v1 : array of integer; size, pos : integer) : integer;
var x : integer;
begin
	if pos < size then
	begin
		writeln(v1[pos]);
		x := j(v1, size, pos+1);
	end;
end;

function k( var v1 : array of real; size, pos : integer) : real;
var x : real;
begin
	if pos < size then
	begin
		writeln(v1[pos]);
		x := k(v1, size, pos+1);
	end;
end;

function l( var v1 : array of boolean; size, pos : integer) : boolean;
var x : boolean;
begin
	if pos < size then
	begin
		writeln(v1[pos]);
		x := l(v1, size, pos+1);
	end;
end;

begin

	writeln(a());
	writeln(b());
	writeln(c());

	v[0] := 5;
	v[1] := 6;
	v[2] := 7;

	w[0] := 1.5;
	w[1] := 1.6;
	w[2] := 1.7;

	y[0] := true;
	y[1] := false;
	y[2] := true;

	writeln(g(v));
	writeln(h(w));
	writeln(i(y));

	aa := j(v, 3, 0);
	bb := k(w, 3, 0);
	cc := l(y, 3, 0);

end.