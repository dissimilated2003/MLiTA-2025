program kav; // каверзный тест
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1 1 0'); 
  writeln(t, '1 1 1 1');
  writeln(t, '0 0 0');
  writeln(t, '1 1');   // должно вывести 4
  writeln(t, '23 97'); 
  write('тест записан в файл'); 
  close(t)
end.