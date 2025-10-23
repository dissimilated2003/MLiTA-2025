program zasor5;
var
  t2: text;
begin
  assign(t2, 'input.txt'); 
  rewrite(t2);
  writeln(t2, '5');
  writeln(t2, '..#..');
  writeln(t2, '..#..');
  writeln(t2, '#####');
  writeln(t2, '..#..');
  write(t2,   '..#..'); 
  writeln('тест записан в файл');
  close(t2)
end.