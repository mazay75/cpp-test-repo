IF xAlm=1 OR xFire=1 OR xAuto=0 THEN START1:=0; START2:=0; START:=0;

ELSE

	IF (xStart OR wCmdStartStop=1 AND xRemote AND xAuto) OR (xAuto AND NOT xRemote) THEN START1:=1; END_IF;
	IF ((xStop OR wCmdStartStop=2) AND xRemote AND xAuto) THEN START1:=0; END_IF;
	
	IF (xStartBlock AND xRemote AND xAuto AND (xStop OR wCmdStartStop=2)) THEN START2:=0; 	xFlag1:=1;
	ELSE IF (xStartBlock=0 AND xRemote AND xAuto) THEN START2:=0;END_IF
		
	IF (xStartBlock AND xRemote AND xAuto) AND NOT xFlag1 THEN START2:=1; END_IF

END_IF
END_IF

IF xStartBlock=0 OR wCmdStartStop=1 OR xStart THEN xFlag1:=0;END_IF

START:=START1 OR START2;

TON1(IN:=xStart OR wCmdStartStop=1,PT:=INT_TO_TIME(3000));

IF TON1.Q THEN xStart:=0; wCmdStartStop:=0;
END_IF

TON2(IN:=xStop OR wCmdStartStop=2,PT:=INT_TO_TIME(3000));

IF TON2.Q THEN xStop:=0; wCmdStartStop:=0;
END_IF

B_TRIG1(	CLK:=xAuto);
IF B_TRIG1.Q THEN START1:=0; START2:=0; START:=0; 
END_IF
R_TRIG1 (CLK:=xRemote);
IF R_TRIG1.Q THEN START1:=0; START2:=0; START:=0; 
END_IF

IF wCmdStartStop>3 THEN  wCmdStartStop:=0;	
END_IF


//БЛОК ДЛЯ УПРАВЛЕНИЯ  УСТАНОВКАМИ, ИМЕЮЩИМИ ОТДЕЛЬНЫЙ ПЕРЕКЛЮЧАТЕЛЬ "МУ-ДУ"
// СО СБЛОКИРОВКОЙ 
//ЗДЕСЬ ЕСЛИ ДАЖЕ БУДЕТ СИГНАЛ СО СБЛОКИРОВКИ И ПОСТУПИТ СИГНАЛ НА ВЫКЛЮЧЕНИЕ СО СКАДЫ ИЛИ С ПУЛЬТА, 
//ТО УСТАНОВКА БУДЕТ ВЫКЛЮЧЕНА, ИГНОРИРУЯ при этом сигнал от сблокировки