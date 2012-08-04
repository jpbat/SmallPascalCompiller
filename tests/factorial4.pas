program p;
var n : integer;
function factorial(n: integer): integer;
 begin
  if n = 0 then
    factorial := 1
   else
    factorial := n*factorial(n-1)
 end;

begin
val(paramstr(1), n);
writeln(factorial(n));
end.

