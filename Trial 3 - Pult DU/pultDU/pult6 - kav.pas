program notNorm; // каверзный тест
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1 1 1'); 
  writeln(t, '1 1 1 1');
  writeln(t, '1 1 1');
  writeln(t, '1 0');   // должно вывести 2: кл. 9,потом стрелка вверх
  writeln(t, '23 10'); 
  write('тест записан в файл'); 
  close(t)
end.