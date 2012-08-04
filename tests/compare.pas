program compare;
 
var
 a, b: integer;
 
begin
  val(paramstr(1), a);
  val(paramstr(2), b);
  if (a < b) then writeln(b);
  if (a = b) then writeln(b);
  if (a > b) then writeln(b);
end.
