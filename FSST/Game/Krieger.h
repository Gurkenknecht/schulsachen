// Autor: Almin Hasanovic

#ifndef FORGOTTEN_H
#define FORGOTTEN_H

#include "Bauer.h"
#include <conio.h>
#include <iostream>
#include <windows.h>
#include <string>
#include <math.h>   

#define MAX_AMMO	5
#define MAX_HANDO	1
#define MAX_THE_WORLD_LENGHT	3
#define MAX_THE_WORLD_NUTZUNGEN	1
#define COOLDOWN	-2
class Forgotten : public Bauer
{
protected:

	int  armor;		// reduces the damage Heros gets
	char block;		// is blocking active?
	char spaste;
	char bullet;
	
	bool isMoving, pick,isAttacked;
	int ammoAnz, kostenStark,kostenMittel,kostenleicht;//AmmoAnzahl und die Kosten der einzelnen Schüsse
	int anzHando, worldDauer,worldAnz, trueHP;//Za Hando und andere Fähigkeiten-Ressourcen
	int spek, xSin,yCos; //Farbe und Variablen für Funktionen
public:
	
	Forgotten()
	{
		strcpy(autorName, "Almin Hasanovic");
		strcpy(heroName, "Forgotten");
		
		life       = MAX_LIFE/2;
		damage     = STD_DAMAGE;
		range      = 80;
		mana       = MAX_MANA;
		move       = MAX_MOVE/2+1;
		block      = 80;
		spek =0;
		width =2;
		bodyCol    = WHITE;
		headCol    = WHITE;
		handCol    = WHITE;
		
		bodyC = 219;
		ammoAnz=MAX_AMMO;
		kostenStark=3;
		kostenMittel=2;
		kostenleicht=1;
	//219 = FullBLock  			254 = halfblock
		bullet =254;
		isMoving=false;
		worldAnz = MAX_THE_WORLD_NUTZUNGEN;
		worldDauer = COOLDOWN;
		anzHando = MAX_HANDO;
		isAttacked=false;
		trueHP=life;
	}
	
	


  /**/
 	void HKreis(int x0, int y0, int radius, char zeichen)
	{
		int dx, dy;
		for( dx=0,dy=radius; dx<=dy; dx++ )
		{
		
			if(dx*dx+dy*dy > radius*radius+1) dy--;			
			Draw(x0-dx,y0+dy,zeichen);
			Draw(x0-dx,y0-dy,zeichen);			
			Draw(x0-dy,y0+dx,zeichen);
			Draw(x0-dy,y0-dx,zeichen);
		}
	}
 	
	void ShowMan()
	{	
		if(pick ==false)
		{		
		setcolor(WHITE);
		Text(x,26,"PICK ME");				
		}
		
		spek++;
		spek%=10;
		setcolor(spek);
		Kreis(x,height,0,bodyC);
		setcolor(spek+3);
		Kreis(x,height,3,bodyC);
		
    }
    void ClearText()
    {
    
		Text(x,27,"                                      ");
		Text(x,26,"                                      ");
		Text(x,25,"                                      ");
	}
    
	
	//pAt
	virtual void Attack()
	{
		isAttacked =false;
		ClearText();
		int penality;
		Text(x,27,"1 = Stark(Kosten=3) "); 
		Text(x,26,"2 = Mittel(Kosten=2)");
		Text(x,25,"3 = Leicht(Kosten=1)");
		
		short sp;
    	if(side == 'l') 
		{
			sp = 1;
		}
		else
		{
			sp=-1;
		}
    	
	        
		spaste = getch();		
		if(ammoAnz<=0)
		{ 
		damage=0;
		}		
		else{
			
			switch(spaste) {
  				case '1':
    			if(ammoAnz>=kostenStark)
			{
				//doppelter schaden dreifache kosten
			damage=12;
			penality=BulletCount(kostenStark);
			}
			else
			{
				penality=BulletCount(kostenStark);	
				damage = 12-penality*4;
			}
 			break;
 			   
 			case '2':
 				if(ammoAnz>=kostenMittel)
			{
				//erhöhter schaden doppelte kosten
			damage=10;
			penality=BulletCount(kostenMittel);
			}
			else
			{
				penality=BulletCount(kostenMittel);
				damage = 10-penality*5;
			}
  	  		break;
  	  		
  	  		case '3':
  	  			if(ammoAnz>=kostenleicht)
			{
				//normaler schaden normale kosten
			damage=6;
			penality=BulletCount(kostenleicht);
			}
			else
			{
				damage = 0;
			}
  	  		break;
  	  			
 		 default: damage=0; break;    
		}	
		
		ShowLife();
		}
	//Attacke endet
		if(worldDauer<=0)
		{
			enemy->ShowBlock();
		}
        ShowAttack();
        enemy->BeAttacked();
        if(worldDauer>0)
        {	
        	if(isMoving==false)
			{
			TheWorld();	
			}        	
        	return;
		}
        enemy->ClearBlock();
        enemy->Show();
        if(isMoving==false)
		{
			TheWorld();	
		}   
	
    }


virtual void Show()
	{
       ShowMan();
	}
virtual void ShowAttack()
	{
        int dx, dy;
		ClearText();
		if(damage>0){		
		for( dx=1,dy=15; dx>(-range); dx-- )
		{
			
			setcolor(weaponCol);
            Draw(dx,dy,bullet);
            Draw(dx-1,dy,bullet);
			Sleep(15);
			Draw(dx,dy,' ');
			Draw(dx-1,dy,' ');
			
			spek = (-dx/8)%10;
			
			ShowMan();
        }
	}
	else
	{
	if(ammoAnz>0)
	{
		Text(x,25,"Keine Attack gewählt");
	}
	else
	{	
		Text(x,25,"Keine Munition");
	}

	}
		
    }
int BulletCount(int bulletVerbrauch)
  {
  	int unterSchritt;
  	ammoAnz-= bulletVerbrauch; 	
  	
  	if(ammoAnz < 0)
  	{
  		unterSchritt = -ammoAnz;
  		ammoAnz =0;
	}
	else
	{
		unterSchritt=0;
	}
		
	return unterSchritt;
  }
  
  virtual void ShowVictory() 
  {
  	PlaySound(TEXT("SoundEffects\\Dead.wav"), NULL,SND_ASYNC);
  	Sleep(100);
  	

  	for(int i=0;i<50;i++)
	{
	Sleep(100);
	ShowMan();
	}
  }
  
	void EndOfEverything()
	{
		PlaySound(TEXT("SoundEffects\\Dead.wav"), NULL,SND_ASYNC);
		
		setcolor(RED);
		Text(x,25,"Du Hast das Ende erreicht");
		Sleep(5000);
		
		Text(x,25,"Dein Versuch zu betruegen ist fehlgeschlagen");
		Sleep(6450);
		
		setcolor(BLACK);
		Text(x,25,"Dein Versuch zu betruegen ist fehlgeschlagen");
		
		setcolor(RED);
		Text(x,25,"Wahre Macht muss verdient werden");
		Sleep(4450);
		
		ClearText();
		
		Text(x,26,"Wer sicht seinem Schicksal nicht stellt");
		Text(x,25,"Verliert");
		Sleep(5000);
	
		for(int i=80;i>-16;i--)
		{
			
			Sleep(0);
			setcolor(WHITE);
			Kreis(0,20,i,219);	
			setcolor(YELLOW);		
			Kreis(0,20,i+1,219);		
			Kreis(0,20,i+2,219);
			setcolor(RED);
			Kreis(0,20,i+3,219);
			setcolor(BLACK);
			Kreis(0,20,i+15,219);
				
		}
		ClearText();
		ShowMan();
		enemy->life=0;
	}
	
	
	void Schutz()
	{
		life = trueHP;
	}
	
    /***/
     virtual void ShowDeath()
    {
    
    	if( life > 0)
		{
			if(isAttacked ==false)
    		{
    		Schutz();
    		ClearText();
    		Text(x,26,"Effekt neutralisiert");
    		enemy->life=0;
			}
			
		 return;
		}  // still alive
    	ShowMan();
    	bool played= PlaySound(TEXT("SoundEffects\\Dead.wav"), NULL,SND_ASYNC);
    	Sleep(1000);
    	Text(x,25,"Change da world");
    	Sleep(2500);
    	Text(x,25,"my final message");
    	Sleep(2000);
    	Text(x,25,"my final message Goodbye");
    	Sleep(4300);
    	ClearText();
		Clear();
	}
    
   
    
    int BeAttacked()
    {
    	int damage = enemy->DoAttack();
    	
    	if( damage < armor )
		{
			ShowLife();
			return 0;
		}
    	if(damage > 10)
    	{
    		EndOfEverything();
    		return 0;
		}
    	damage -= armor;
    	life -= damage;
    	trueHP = life;
    	
    	//AAAAAAAAAAAAAATTTTACCCKEEEEED
    	isAttacked=true;
    	
    	ShowLife();
    	return damage;
    }
    
     virtual int BeMagicAttacked()
	{
		
		ClearText();
		Text(x,25,"Magie Counter");
		Sleep(600);
		ClearText();
    	damage = 5;
		enemy->ShowBlock();
        ShowAttack();
        enemy->BeAttacked();
        enemy->ClearBlock();
        enemy->Show();
    	ShowLife();
    	damage=0;
    	return damage;    	
	}
 
 virtual void Move(int wohin)
    {
    	isAttacked =false;
    	ClearText();
    	Text(x,26,"druecke A um anzugreifen");
    	Text(x,25," und deine bewegung zu verkleinern");
    	isMoving=true;
    	short sp;
    	if(side == 'l') 
		{
			sp = -1;
		}
		else
		{
			sp=1;
		}
    	
    	spaste = getch();
    	if(spaste =='a')
		{
		damage =4;
		enemy->ShowBlock();
        ShowAttack();
        enemy->BeAttacked();
        enemy->ClearBlock();
        enemy->Show();
    	ShowLife();
    	damage=0;
		     if(wohin > +move) wohin = +move;
       		 if(wohin < -move) wohin = -move;
        
		}		
		else
		{
			if(wohin > +move) wohin = +move*2;
       		if(wohin < -move) wohin = -move*2;
		}
		ClearText();
    	// move = speed = range of movement
        setcolor(WHITE);
        for(int i =width+2;i>=0;i--)
     	{
     		
     			
     		Linie(x+i,0,0,35,219);
     		Linie(x-i,0,0,35,219);
     		Sleep(60);
		}
		
		   setcolor(BLACK);
        for(int i =width+2;i>=0;i--)
     	{
     		
     		Linie(x+i,0,0,35,219);
     		Linie(x-i,0,0,35,219);    		 		
     		Sleep(30);
		}
     	
   // positiv wohin => ZUR MITTE
        for(int i=0; i<wohin; i++)
        {
            if( x<=-MIDDLE+width+1 ) break;
            if( x + enemy->x <= MIN_DISTANCE
			    + width + enemy->width ) break;
            
            x--;                // Move Fighter          
        }
        
        // negativ wohin => NACH AUSSEN
        for(int i=0; i>wohin; i--)
        {
        	
            if( x >= MIDDLE-width-1 ) break;            
            x++;                // Move Fighter
        }
        
		
        for(int i =0;i<=width+2;i++)
     	{
     		Linie(x+i,0,0,35,219);
     		Linie(x-i,0,0,35,219);
     		Sleep(30);
		}
		
		   setcolor(BLACK);
        for(int i =0;i<=width+2;i++)
     	{
     		Linie(x+i,0,0,35,219);
     		Linie(x-i,0,0,35,219);
     		Sleep(30);
		}
        
        
        Show();
        enemy->Show();
        isMoving=false;
        TheWorld();
    }
    
    virtual void ShowLife()
	{
	
		int i;
		short x,y;
		char zeile[WIDTH+1];
		for(i=0; i<WIDTH;i++) zeile[i]=' ';
		zeile[WIDTH]=0;
		if(side == 'l')
		{
			y=1;
			x=1;
		}
		else
		{
			y=2;
			x=MIDDLE;
		}
		gotoxy(0,y);
		cout << zeile;	// Clear Life
		gotoxy(0,y+2);
		cout << zeile;	// Clear Mana
		
		if( life > 15)     setcolor(GREEN);
		else if( life > 7) setcolor(YELLOW);
		else               setcolor(RED);
		gotoxy(x,y);
		if( life <= 0 )
		{
			cout << "+ DU BIST TOT +";
		}	
		else
		{
			// LIFE
			for(i=0;i<life;i++) zeile[i]=219;
			zeile[life]=0;
			cout << "Life: "<<zeile;
			// SHIELD
			setcolor(WHITE);
			for(i=0;i<shield;i++) zeile[i]=219;
			zeile[shield]=0;
			cout << zeile;
		}
		
		setcolor(YELLOW);
		for(i=0; i<WIDTH;i++) zeile[i]=' ';
		for(i=0;i<ammoAnz;i++) zeile[i*MAX_AMMO]=219;
		zeile[ammoAnz*MAX_AMMO]=0;
		gotoxy(x,y+2);
		cout << "Ammo: "<<zeile;
	}
	
	
	
	
	
  
	
    //MAGIE STUFF
    //pMag
     virtual void Magic()
	{
		isAttacked =false;
		int zaHoehe=16, zaRadius=17, zaReichweite=30;
		Text(x,27,"r=Nachladen");
		Text(x,26,"z=ZA HANDO");
		Text(x,25,"w=The World");
		spaste = getch();
		switch(spaste)
		{
			case 'w': if(worldAnz!=0&&worldDauer==COOLDOWN)
			{
				ClearText();
				worldDauer = MAX_THE_WORLD_LENGHT;
				worldAnz--;
				PlaySound(TEXT("SoundEffects\\Dead.wav"), NULL,SND_ASYNC);
				
				setcolor(YELLOW);
				Kreis(x,30,4,219);
				for(int i=0;i>-7;i--)
				{	
					
					
					setcolor(BLACK);
					xSin= sin(i+1)*3;
					yCos= cos(i+1)*3;
					Linie(x,30,xSin,yCos,219);
					
					xSin= sin(i)*3;
					yCos= cos(i)*3;
					setcolor(YELLOW);
					Kreis(x,30,4,219);
					Linie(x,30,xSin,yCos,219);
					Sleep(200*(-i));
					
				}
				
				setcolor(BLACK);
				Linie(x,30,xSin,yCos,219);
				Kreis(x,30,4,219);
				setcolor(WHITE);
				break;
				
			}
		//Nachladen
			case 'r': ammoAnz=MAX_AMMO;
			ShowLife();
			break;
			
			
			case'z': 
			if(anzHando!=0)
			{			
			PlaySound(TEXT("SoundEffects\\Dead.wav"), NULL,SND_ASYNC);
			setcolor(BLUE);
			Sleep(1000);
			HKreis(-(enemy->x+21),zaHoehe,zaRadius,219);
			setcolor(LIGHTBLUE);
			HKreis (-(enemy->x+20),zaHoehe,zaRadius,219);		
			HKreis(-(enemy->x+19),zaHoehe,zaRadius,219);
			
			Sleep(1500);
			
			setcolor(BLACK);
			
			HKreis(-(enemy->x+21),zaHoehe,zaRadius,219);
			HKreis (-(enemy->x+20),zaHoehe,zaRadius,219);
			HKreis(-(enemy->x+19),zaHoehe,zaRadius,219);
			
			for(int i=0;i<=zaReichweite;i+=1)
			{
				
				enemy->Clear();
				//bestimmt mit dem i die Geschwindigkeit
				enemy->x+=1;
				enemy->Show();
		 	}
		 	ClearText();
		 	anzHando--;
		 	break;
			//if enden
			}	
			else
			{
			ClearText();
			Text(x,25,"Keine Za Hando vorhanden :c");	
			break;
			}
		}
	
	//FAST ENDE
	TheWorld();
	}
	
	void TheWorld()
	{
		
			if(worldDauer>0)
			{			
			ClearText();
			Text(x,25,"Mach was");
			if(worldDauer>COOLDOWN)worldDauer--;
			spaste = getch();
			switch(spaste)
			{
				case 'a':
				case 'A': Attack(); break;
	            case 's':
	            case 'm':
				case 'M': Magic(); break;
	            case 'f':
	            case 'v':
				case 'V': Move(+100); break;
	            case 'd':
	            case 'r':
				case 'R': Move(-100); break;
				case '+': Move(1); break;
				case '-': Move(-1); break;
			}
		}
	}
	
    virtual void ShowMagic()
	{
		// No MAGIC => do nothing
	}
     
	virtual void Clear()
    {
        char saveBody   = bodyC;
        bodyC   = ' ';
        Show();
        bodyC   = saveBody;

		ClearText();
    }
   
 
    
    void ShowStart()
	{
		pick=true;
		Clear();
		Show();
	
	}
};

#endif
