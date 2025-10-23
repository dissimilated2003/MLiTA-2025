program test3; // здесь уже проверяется работа алгоритма BFS
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 0 0 1'); 
  writeln(t, '0 0 0 1');
  writeln(t, '0 0 0');
  writeln(t, '0 0');
  writeln(t, '37 99'); // должен вывести 38, т.к нижними стрелками ему до 99 
  write('тест записан в файл'); // добраться быстрее, чем верхними до 99
  close(t)
end.