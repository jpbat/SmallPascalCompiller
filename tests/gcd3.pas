PROGRAM gcd;

VAR a,b,c,d,i:integer;

BEGIN
	val(paramstr(1), a);
	val(paramstr(2), b);
	IF a <= b THEN c := a; 
	c := b; 
	FOR i := 1 TO c DO
	BEGIN
	      IF (a MOD i = 0) AND (b MOD i = 0) THEN 
	      d := i; 
	END;
	writeln(d); 
END.
