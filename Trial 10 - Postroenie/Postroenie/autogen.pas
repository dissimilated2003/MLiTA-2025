program TestGenerator;
uses crt;
const
  TOTAL_COMMANDS = 200000;
  MAX_HEIGHT = 100000;
  INPUT_FILE = 'input.txt';
var
  f: Text;
  i, cmdType, currentSoldiers, removePos, newHeight: Integer;
  soldiers: array of Integer;
begin
  Randomize;
  Assign(f, INPUT_FILE);
  Rewrite(f);
  currentSoldiers := 0;
  SetLength(soldiers, 0);
  Writeln(f, TOTAL_COMMANDS);
  for i := 1 to TOTAL_COMMANDS do
  begin
    if (currentSoldiers = 0) then
      cmdType := 1 
    else
    begin
      if (Random(100) < 70) then
        cmdType := 1
      else
        cmdType := 2;
    end;
    if (cmdType = 1) 
    then
      begin
        newHeight := 1 + Random(MAX_HEIGHT);
        Writeln(f, '1 ', newHeight);
        SetLength(soldiers, currentSoldiers + 1);
        soldiers[currentSoldiers] := newHeight;
        Inc(currentSoldiers);
      end
    else
      begin
        removePos := 1 + Random(currentSoldiers);
        Writeln(f, '2 ', removePos);
        Dec(currentSoldiers);
        soldiers[removePos - 1] := soldiers[currentSoldiers];
        SetLength(soldiers, currentSoldiers);
    end;
  end;
  Close(f);
  Writeln('тест записан в ', INPUT_FILE);
end.