Program PascalsTriangle;
  var n : integer;

function Pascal(r : Integer): integer;
var i, c, k : Integer;

begin
  (*for i := 0 to r-1 do
  begin
    c := 1;
    for k := 0 to i do
    begin
      writeln(c);
      c := (c * (i-k)) div (k+1);
    end;
  end;*)
  Pascal := r;
end;
 
begin
  writeln(Pascal(5));
end.
