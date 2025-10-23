program pultGen;
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 0 1 1');
  writeln(t, '1 1 1 1');
  writeln(t, '1 1 1');
  writeln(t, '1 1');
  writeln(t, '23 52');
  write('тест записан в файл');
  close(t)
end.