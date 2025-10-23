program plusplus; // тест +
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 1 0 1'); 
  writeln(t, '0 0 0 1');
  writeln(t, '0 0 0');
  writeln(t, '0 1');   // должно вывести 2
  writeln(t, '95 1'); 
  write('тест записан в файл'); 
  close(t)
end.