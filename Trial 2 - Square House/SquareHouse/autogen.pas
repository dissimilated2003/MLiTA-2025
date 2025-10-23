program autogen; // 2.7 kvadratny dom
uses crt;
const 
  n = 7;
  m = 50;
var 
  fin: text;
  x, y, d: integer;
begin
  randomize;
  assign(fin, 'input.txt');
  rewrite(fin);
  writeln(fin, n, ' ', m);
  writeln(n, ' ', m);
  for var i := 1 to n
  do
    begin
      d := random(m div 2);
      if d = 0
      then
        d := d + 1;
      x := random(m - d);
      y := random(m - d);
      writeln(fin, $'{d} {x} {y}');
      writeln($'{d} {x} {y}');
    end;
  close(fin)
end.