program pult1; // нихера не работает
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1 1 0');
  writeln(t, '1 1 1 0');
  writeln(t, '1 1 1');
  writeln(t, '0 1');
  writeln(t, '5 77'); // должен вывести -1,т.к для 77 кнопка -- неисправна
  write('тест записан в файл');
  close(t)
end.