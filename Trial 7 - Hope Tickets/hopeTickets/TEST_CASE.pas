program testcase;
var
  t: text;
  sel: integer;
procedure print1(t: text); // 99999899998999989999
begin
  rewrite(t);
  writeln(t, '20');
  writeln(t, '9999999999999999999900000100001000010000');
  writeln('тест ', sel, ' записан')
end;

procedure print2(t: text); // 0
begin
  rewrite(t);
  writeln(t, '10');
  writeln(t, '55667766556464868484');
  writeln('тест ', sel, ' записан')
end;

procedure print3(t: text); // 3
begin
  rewrite(t);
  writeln(t, '10');
  writeln(t, '00000000019999999999');
  writeln('тест ', sel, ' записан')
end;

procedure print4(t: text); // 5
begin
  rewrite(t);
  writeln(t, '2');
  writeln(t, '0628');
  writeln('тест ', sel, ' записан')
end;

procedure print5(t: text); // 79999
begin
  rewrite(t);
  writeln(t, '50'); 
  writeln(t, '1111111111111111111111111111111111111111111111111170000000000000000000000000000000000000000000000000');
  writeln('тест ', sel, ' записан')
end;                                                        //  50

procedure print6(t: text); // 6
begin
  rewrite(t);
  writeln(t, '1');
  writeln(t, '27');
  writeln('тест ', sel, ' записан')
end;

procedure printMax(t: text); // 444444444444444444444444...4444444444444444
begin
  rewrite(t);
  var lim := 500; // работает с оооооочень большими числами разрядностью до 10^6
  writeln(t, lim);
  for var i := 1 to lim
  do
    write(t, '8');
  for var i := 1 to lim
  do
    write(t, '5');
  writeln('тест ', sel, ' записан')
end;

procedure print8(t: text); // 61831569003
begin
  rewrite(t);
  writeln(t, '12');
  writeln(t, '000010000000938168430999');
  writeln('тест ', sel, ' записан')
end;

procedure print9(t: text); // 12340763548934983985123501834918984983980140955213418310542
begin
  rewrite(t);
  writeln(t, '91');
  writeln(t, '11111111111111111111111111111111111111100000000000000000000000000000000000000979999345048719747012701912318098209702370283087659236451065016014876498165081015016019859044786581689458');
  writeln('тест ', sel, ' записан')
end;

// ------------------------------------------------------------------------------
begin
  assign(t, 'input.txt');
  read(sel);
  case sel of
    1: print1(t);
    2: print2(t);
    3: print3(t);
    4: print4(t);
    5: print5(t);
    6: print6(t);
    7: printMax(t);
    8: print8(t);
    9: print9(t)
    else
      writeln('неверный цифра')
  end;
  close(t);
end.