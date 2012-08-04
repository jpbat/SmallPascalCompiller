PROGRAM fact1;

VAR n:integer;


FUNCTION fact(n:integer):integer;

VAR prod1, i:integer;

BEGIN 
     BEGIN 
          prod1:=1;
          for i := n downto 1 do
		begin
          	prod1 := prod1*i;
		end
     END; 
     fact := prod1;
END;

BEGIN
     n := 5; 
     writeln(fact(n));
END.
