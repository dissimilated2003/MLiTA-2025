program gen;
var
  t: text;
procedure printGen(t: text); // генеральный
begin
  writeln(t, '10 7');
  writeln(t, '3 5 12 18 25 40 47 47 48 49'); //---------------- 4
end;

procedure printKaverz(t: text); // дубликаты
begin
  writeln(t, '5 4');
  writeln(t, '8 8 8 12 12'); //-------------------------------- 6
end;  

procedure printPipec(t: text); // дистанция в 3
begin
  writeln(t, '7 7');
  writeln(t, '3 5 7 10 12 14 17'); //-------------------------- 4
end;

procedure printVinegret(t: text); // бронебойный
begin
  writeln(t, '10 4');
  writeln(t, '4 5 7 8 8 8 12 12 17 21'); //-------------------- 10
end;

procedure parasha(t: text); // парашный засор
begin
  writeln(t, '20 2');
  writeln(t, '2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 4'); //---- 19
end;

procedure parasha2(t: text); // полный парашный засор
begin
  writeln(t, '20 1');
  writeln(t, '1 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 3'); //---- 36 (18+18)
end;
  
begin
  assign(t, 'input.txt');
  rewrite(t);
  var i: integer;
  read(i);
  
  case i of 
    1: printGen(t);
    2: printKaverz(t);
    3: printPipec(t);
    4: printVinegret(t);
    5: parasha(t);
    6: parasha2(t)
    else 
      writeln('неверная цифра')
  end;
  close(t);
  writeln('тест записан');
end.