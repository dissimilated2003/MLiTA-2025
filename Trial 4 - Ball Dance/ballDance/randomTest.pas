program randomAB;
uses
    crt;
const
    n = 100;
var
    t: text;
    ab: string;
begin
    randomize;
    ab := '';
    for var i := 1 to n
    do
        if random(2) = 0
        then
            ab := ab + 'a'
        else
            ab := ab + 'b';
        
    assign(t, 'input.txt');
    rewrite(t);
    writeln(t, n);
    writeln(t, ab);
    close(t);
    
    writeln('тест записан в файл');
    writeln($'n: {n}');
    writeln($'ab: {ab}');
end.