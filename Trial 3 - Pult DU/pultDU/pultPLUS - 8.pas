program plusplus; // тест +
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 0 0 1'); 
  writeln(t, '0 0 0 1');
  writeln(t, '0 0 1');
  writeln(t, '1 1');   // должно вывести 6
  writeln(t, '10 95'); 
  write('тест записан в файл'); 
  close(t)
end.