program general;
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1');
  writeln(t, '+');
  writeln(t, '1 10');
  close(t);
  writeln('тест записан в файл')
end.