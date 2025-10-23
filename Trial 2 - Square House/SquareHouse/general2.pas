program general2;
var
  f: text;
begin
  assign(f, 'input.txt');
  rewrite(f);
  writeln(f, '1 100');
  writeln(f, '100 0 0');
  close(f);
  writeln('тест записан в файл')
end.