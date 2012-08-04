PROGRAM prime_generation;

VAR i,j,k,n:integer;

BEGIN 
	n := 100;
     FOR i := 2 TO n DO 
     BEGIN 
          k := 0; 
          FOR j := 1 TO n DO 
          	IF i MOD j = 0 THEN
				k := k+1; 
          IF k <= 2 THEN
			writeln(i); 
     END; 
END.
