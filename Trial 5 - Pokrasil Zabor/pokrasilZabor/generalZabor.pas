program general;
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '15 2');
  writeln(t, '0+000+++0+0+++0');
  writeln(t, '2 3');
  writeln(t, '3 5');
  close(t);
  writeln('тест записан в файл')
end.