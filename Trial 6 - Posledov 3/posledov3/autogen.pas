program autogen;
uses crt;
const
  n = 1000000;
  diff = 40;
  max_step = 10;
var
  t: text;
  i, prev, step: integer;
begin
  randomize;
  assign(t, 'input.txt');
  rewrite(t);
  
  writeln(t, n, ' ', diff);
  prev := random(100);
  write(t, prev, ' ');

  for i := 2 to n 
  do
    begin
      step := random(max_step) + 1;
      prev := prev + step;
      write(t, prev, ' ');
    end;
  close(t);
  writeln('тест записан в файл');
end.