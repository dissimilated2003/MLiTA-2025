program test_case;
const
  format = '.txt';
var
  t: text;
  sel: integer;
  
procedure print_1(t: text); // должн быть 1
begin
  writeln(t, '10 2');
  writeln(t, '0++++++++0');
  writeln(t, '10 3');
  writeln(t, '2 1');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_2(t: text); // должно вылететь 1
begin
  writeln(t, '10 3');
  writeln(t, '0+++00+++0');
  writeln(t, '10 3');
  writeln(t, '5 1');
  writeln(t, '9 1');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_3(t: text); // должно 2
begin
  writeln(t, '10 3');
  writeln(t, '0000000000');
  writeln(t, '10 3');
  writeln(t, '2 1');
  writeln(t, '7 1');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_4(t: text); // бесплатно, 0
begin
  writeln(t, '10 2');
  writeln(t, '++00000000');
  writeln(t, '2 1');
  writeln(t, '1 0');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_5(t: text); // должно вывести 1
begin
  writeln(t, '20 2');
  writeln(t, '+0++++++++++++++++0+');
  writeln(t, '19 2');
  writeln(t, '4 1');
  writeln('тест ', sel, ' записан в файл')
end;

begin
  assign(t, 'input' + format);
  rewrite(t);
  readln(sel);
  case sel of
    1: print_1(t);
    2: print_2(t);
    3: print_3(t);
    4: print_4(t);
    5: print_5(t);
  else
    writeln('не то число');
    halt(-1)
  end;
  close(t)
end.