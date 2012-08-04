PROGRAM fibonacci_series;

VAR a,b,j,n: integer;

function fib(a, b, j:integer): integer;
BEGIN 
     IF j>0 THEN 
     BEGIN 
          WHILE j <> a DO 
          BEGIN 
          	writeln(a); 
          	fib := fib(b, a+b, j-1); 
          END; 
     END; 
END; 

BEGIN
     n := 10;
     writeln(fib(0, 1, n)); 
END.
