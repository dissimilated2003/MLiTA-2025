program general;
var
  f: text;
begin
  assign(f, 'input.txt');
  rewrite(f);
  writeln(f, '6 10');
  writeln(f, '3 1 2');
  writeln(f, '3 7 7');
  writeln(f, '4 0 6');
  writeln(f, '5 5 0');
  writeln(f, '2 4 5');
  writeln(f, '1 2 0');
  close(f);
  writeln('тест записан в файл')
end.