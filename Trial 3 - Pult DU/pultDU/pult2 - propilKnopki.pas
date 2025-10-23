program propilKnopki; // нихера нет кнопок 0-9
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '0 0 0 1');
  writeln(t, '0 0 0 1');
  writeln(t, '0 0 0');
  writeln(t, '1 0');
  writeln(t, '1 99'); // должен вывести 2
  write('тест записан в файл');
  close(t)
end.