program randButtons; // здесь уже проверяется работа алгоритма BFS
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 1 0 1'); 
  writeln(t, '1 0 0 1');
  writeln(t, '0 1 0');
  writeln(t, '1 0');   // должно вывести 9
  writeln(t, '24 76'); // идёт в 82, далее 6 нажатий стрелки вниз
  write('тест записан в файл'); 
  close(t)
end.