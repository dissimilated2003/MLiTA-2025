program plusplus; // тест +
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 0 0 0'); 
  writeln(t, '1 0 0 0');
  writeln(t, '0 0 0');
  writeln(t, '1 0');   // должно вывести -1
  writeln(t, '42 0'); 
  write('тест записан в файл'); 
  close(t)
end.