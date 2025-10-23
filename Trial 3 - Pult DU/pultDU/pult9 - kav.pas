program kav; // каверзный тест
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1 1 1'); 
  writeln(t, '1 1 1 1');
  writeln(t, '1 0 1');
  writeln(t, '1 1');   // должно вывести 4
  writeln(t, '23 98'); 
  write('тест записан в файл'); 
  close(t)
end.