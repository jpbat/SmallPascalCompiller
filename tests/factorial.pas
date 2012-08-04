PROGRAM factorial;

VAR x:integer;

FUNCTION fact(n:integer): integer;

BEGIN 
     IF n <= 1 THEN fact := 1 
     ELSE fact := n*fact(n-1); 
END;

BEGIN 
     val(paramstr(1), x);
     writeln(fact(x));
END.
