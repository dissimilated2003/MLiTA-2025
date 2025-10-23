program gen224;
var
  t: text;
begin
  assign(t, 'input.txt');
  rewrite(t);
  writeln(t, '1000000 2');
  for var i := 1 to 999999
  do
    write(t, '2 ');
  write(t, '4');
  close(t);
  writeln('тест записано')
end.