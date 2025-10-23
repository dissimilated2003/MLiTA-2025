program pult1pustoiV2; // нихера не работает
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1 1 1 0');
  writeln(t, '1 1 1 0');
  writeln(t, '1 1 1');
  writeln(t, '0 1');
  writeln(t, '5 9'); // должен вывести 1,т.к для перехода на 0-9 каналы нужно 1 нажатие
  write('тест записан в файл');
  close(t)
end.