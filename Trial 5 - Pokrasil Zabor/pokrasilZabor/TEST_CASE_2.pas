program test_case; //боевые тесты 5 шт
const
  format = '.txt';
var
  t: text;
  sel: integer;
  
procedure print_1(t: text); // должeн быть 2
begin
  writeln(t, '15 2');
  writeln(t, '+000000+++++++0');
  writeln(t, '3 1');
  writeln(t, '8 2');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_2(t: text); // должно вылететь 13
begin
  writeln(t, '15 2');
  writeln(t, '0+000+++0+0+++0');
  writeln(t, '2 3');
  writeln(t, '3 5');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_3(t: text); // должно вывести 9: 1 доска 2(11) + 6 досок 7(13,1,2,3,4,5)
begin
  writeln(t, '13 3');
  writeln(t, '+0000+++++0+0');
  //          33333+++++1+3 => 7+2=9
  writeln(t, '1 2');
  writeln(t, '2 3');
  writeln(t, '6 7');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_4(t: text); // выдать 14
begin
  writeln(t, '14 3');
  writeln(t, '+000+00++++0+0');
  //          3333333++++333 => 7+7=14
  writeln(t, '1 3');
  writeln(t, '3 5');
  writeln(t, '5 7');
  writeln('тест ', sel, ' записан в файл')
end;

procedure print_5(t: text); // должно вывести 10
begin
  writeln(t, '14 3');
  writeln(t, '+000+00++++0+0');
  //          +333333++++222 => 6+4=10
  writeln(t, '2 3');
  writeln(t, '3 4');
  writeln(t, '6 6');
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