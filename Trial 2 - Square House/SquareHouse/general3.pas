program general;
var
  f: text;
begin
  assign(f, 'input.txt');
  rewrite(f);
  writeln(f, '7 10');
  writeln(f, '3 5 4');
  writeln(f, '4 5 0');
  writeln(f, '2 3 0');
  writeln(f, '3 0 0');
  writeln(f, '5 0 4');
  writeln(f, '3 5 7');
  writeln(f, '2 8 5');
  close(f);
  writeln('тест записан в файл')
end.