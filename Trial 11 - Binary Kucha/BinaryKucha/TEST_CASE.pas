program test_case_binaryHeap;
var
  t: text;
  entry: byte;
procedure push1(var t: text); // 34 9 7
begin                         // 15 15 20
  writeln(t, '3 50');         // 1 26 23
  writeln(t, '34 9 7');
  writeln(t, '0 0 20');
  writeln(t, '0 0 23');
end;

procedure push2(var t: text); // -2 44 43
begin                         // 25 36 24 
  writeln(t, '3 85');         // 62 5 18 
  writeln(t, '0 0 43');
  writeln(t, '25 0 0');
  writeln(t, '0 5 18');
end;

procedure push3(var t: text); // No
begin
  writeln(t, '2 21');
  writeln(t, '0 9');
  writeln(t, '6 0');
end;  

procedure push4(var t: text); // 5 0
begin                         // 0 5
  writeln(t, '2 5');
  writeln(t, '0 0');
  writeln(t, '0 0');
end;  

procedure push5(var t: text); // -1 1 1 1
begin                         // 1 -1 1 1
  writeln(t, '4 2');          // 1 1 -1 1
  writeln(t, '0 1 1 0');      // 1 1 1 -1
  writeln(t, '1 0 0 1');
  writeln(t, '1 0 0 1');
  writeln(t, '0 1 1 0');
end; 
  
begin
  assign(t, 'input.txt');
  rewrite(t);
  readln(entry);
  case entry of
    1: push1(t);
    2: push2(t);
    3: push3(t);
    4: push4(t);
    5: push5(t)
    else
      begin
        writeln('err');
        exit
      end
  end;
  writeln('тест ', entry, ' записан');
  close(t)
end.