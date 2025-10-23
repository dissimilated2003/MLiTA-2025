program checker;
var 
  fout: textfile;
const 
  maxKvadratSize = 1000;
begin
  assign(fout, 'output.txt');
  reset(fout);
  var getN: integer := 0;
  var buff: string;
  while not eof(fout) 
  do
    begin
      readln(fout, buff);
      inc(getN);
    end;
  close(fout);
  reset(fout);
  var kvadrat: array[1..maxKvadratSize, 1..maxKvadratSize] of integer;
  for var i := 1 to getN 
  do
    for var j := 1 to getN 
    do
      read(fout, kvadrat[i, j]);
  close(fout);
  var etalonSum: integer := 0;
  for var j := 1 to getN 
  do
    etalonSum := etalonSum + kvadrat[1, j];
  var isMagic: boolean := true;
  for var i := 1 to getN 
  do
    begin
      var rowSum: integer := 0;
      for var j := 1 to getN 
      do
        rowSum := rowSum + kvadrat[i, j];
      if rowSum <> etalonSum 
      then
        begin
          isMagic := false;
          break;
        end;
    end;

  if isMagic 
  then
    begin
      for var j := 1 to getN 
      do
        begin
          var colSum: integer := 0;
          for var i := 1 to getN 
          do
            colSum := colSum + kvadrat[i, j];
          if colSum <> etalonSum 
          then
            begin
              isMagic := false;
              break;
            end;
        end;
    end;
  if isMagic 
  then
    writeln('квадрат магический (все суммы равны ', etalonSum, ' )')
  else
    writeln('квадрат говно');
end.