program avtoZasor;
uses crt;
const 
  n = 33;
  fieldChar: array[0 .. 3] of char = ('.', '.', '.', '#');
type
  arrLen = array[1 .. n] of char;
  arrMatrix = array[1 .. n] of arrLen;
var
  t1: text;
  test: arrMatrix;
  randSym: char;
  randIndex: integer;
begin
  randomize; // нерандомный рандомайзер))
  assign(t1, 'input.txt');
  rewrite(t1);
  writeln(n);
  writeln(t1, n);
  for var i := 1 to n
  do
    begin
      for var j := 1 to n
      do
        begin
          randIndex := random(4);
          randSym := fieldChar[randIndex];
          test[i][j] := randSym;
          write(test[i][j]);
          write(t1, test[i][j])
        end;
      writeln;
      writeln(t1)
    end;
  close(t1)
end.