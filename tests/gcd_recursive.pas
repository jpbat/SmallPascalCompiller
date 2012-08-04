program gcd;

function gcd_recursive(u, v: integer): integer;
  begin
    if u mod v <> 0 then
        gcd_recursive := gcd_recursive(v, u mod v)
    else
        gcd_recursive := v;
  end;

begin
val(paramstr(1), u);
val(paramstr(2), v);
gcd_recursive(u, v)
end.
