program testLogical;

begin
	if True and False or False and True and True then
		(*isto não devia aparecer*)
		writeln(1);
	if True and False or True then
		(*isto devia aparecer*)
		writeln(5);
end.
