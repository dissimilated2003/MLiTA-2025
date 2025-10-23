program allNorm; // все кнопки рабочие
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1 1 1'); 
  writeln(t, '1 1 1 1');
  writeln(t, '1 1 1');
  writeln(t, '1 1');   // должно вывести 3
  writeln(t, '24 76'); 
  write('тест записан в файл'); 
  close(t)
end.