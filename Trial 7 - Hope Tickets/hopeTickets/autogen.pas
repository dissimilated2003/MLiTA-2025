program autogen;
uses crt;
const
    n = 50;
var
    t: text;
    multiN: integer;
begin
    Randomize;
    assign(t, 'input.txt');
    rewrite(t);
    multiN := 2 * n;
    writeln(t, n);
    for var i := 1 to multiN
    do
        write(t, random(10));
    close(t);
    writeln('тест записан в файл')
end.