program gcd;
var u, v : integer;
function gcd_iterative(u, v: integer): integer;
  var t: integer;
  begin
    while v <> 0 do
    begin
      t := u;
      u := v;
      v := t mod v;
    end;
    gcd_iterative := u;
  end;

begin
val(paramstr(1), u);
val(paramstr(2), v);
writeln(gcd_iterative(u, v));
end.
