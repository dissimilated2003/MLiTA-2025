program test_case;
var
  t: text;
  entry: byte;
procedure push1(var t: text);
begin
  writeln(t, '2');
  writeln(t, '2 2');
  writeln(t, '2 1')
end;

procedure push2(var t: text);
begin
  writeln(t, '7');
  writeln(t, '1 1000');
  writeln(t, '1 100000');
  writeln(t, '2 1');
  writeln(t, '1 999');
  writeln(t, '2 1');
  writeln(t, '1 1000');
  writeln(t, '1 1000');
end;

procedure push3(var t: text);
begin
  writeln(t, '5');
  writeln(t, '1 1');
  writeln(t, '1 2');
  writeln(t, '1 10');
  writeln(t, '2 2');
  writeln(t, '1 7')
end;  
  
begin
  assign(t, 'input.txt');
  rewrite(t);
  readln(entry);
  case entry of
    1: push1(t);
    2: push2(t);
    3: push3(t)
    else
      begin
        writeln('err');
        exit
      end
  end;
  writeln('тест ', entry, ' записан');
  close(t)
end.