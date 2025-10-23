program copyBookTest3;
var
  t2: text;
begin
  assign(t2, 'input.txt'); 
  rewrite(t2);
  writeln(t2, '5');
  writeln(t2, '..#..');
  writeln(t2, '#..#.');
  writeln(t2, '.#..#');
  writeln(t2, '..#..');
  write(t2,   '...#.');
  close(t2);
  writeln('тест записан в файл')
end.