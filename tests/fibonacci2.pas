program f;
var x : integer;
function fib(n: integer): integer;
begin
	if (n = 0) or (n = 1) then
	begin
		fib := n;
	end
	else
	begin
		fib := fib(n-1) + fib(n-2);
	end;
end;
begin
     x:= 10;
     writeln(fib(x));
end.
