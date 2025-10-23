program dancegen;
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '8');
  write(t, 'abbababa');
  close(t);
  write('тест записан в файл')
end.