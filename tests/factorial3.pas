program p;
var n : integer;
function factorial(n: integer): integer;
 var
  i, result: integer;
 begin
  result := 1;
  for i := 2 to n do
  begin
   writeln(result);
   result := result * i;
  end;  
factorial := result
 end;
begin
writeln(factorial(5));
end.
