PROGRAM gcd_recursion;

VAR a,b:integer;

FUNCTION gcd(p, q:integer): integer;

BEGIN 
     IF p<q THEN 
        BEGIN 
             gcd:=gcd(q,p); 
        END
     ELSE 
        IF q=0 THEN 
           BEGIN 
                gcd:=p; 
           END 
        ELSE 
            gcd := gcd(q, p MOD q); 
END;

BEGIN
     val(paramstr(1), a);
     val(paramstr(2), b);
     writeln(gcd(a,b)); 
END.
