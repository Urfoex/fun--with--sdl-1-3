;-----------------------------------------------------------------------------
;  GoASM
; =======
; Dies ist ein Go Spielbrett fuer 2 Spieler.
;
; @author: Manuel Bellersen
; @matrikel: 46958
;-----------------------------------------------------------------------------
    .model small
    .386

;-----------------------------------------------------------------------------
; Hier stehen alle benoetigten Konstanten
;-----------------------------------------------------------------------------
    ; Konstanten
    KEY_ESC             = 1Bh
    VGA_SEGMENT         = 0A000h
    STEIN_MASKE         = 11000000b
    FELDNUMMER_MASKE    = 0011111111111111b
    FELDINDEX_MASKE     = 0000000000000011b

    FELD_FREI       = 00000000b
    FELD_SCHWARZ    = 01000000b
    FELD_WEISS      = 10000000b
    FELD_AUSSEN     = 11000000b

    TRUE    = 11111111b
    YPLUS   = 19
    XPLUS   = 1
    XYMAX   = 360               ; 0 - 360 = 361

;-----------------------------------------------------------------------------
; Der Stack ist im Normalfall 1024 Bytes gross. Das sollte hier auch reichen.
;-----------------------------------------------------------------------------
    .stack                      ; 1024 Bytes

;-----------------------------------------------------------------------------
; Hier stehen alle benoetigten Variablen.
;-----------------------------------------------------------------------------
    .data
    HalloMSG DB "Hallo Ihr zwei. Ich wuensche viel Spass!", "$"
    Spielbrett      DB 91 DUP(00000000b)
    RUECKGABE       DB 00000000b
    STANDARD        DB 00000000b
    ANZAHL          DW 00h
    CHECK_RUND      DB 00000000b
    PUNKTE_SCHWARZ  DW 00h
    PUNKTE_WEISS    DW 00h

;-----------------------------------------------------------------------------
; Hier faengt der eigentliche Code an.
;-----------------------------------------------------------------------------
    .code

;-----------------------------------------------------------------------------
; Das Hauptprogramm:
;   alle moeglichen Einstellungen setzten und das Spiel aufrufen.
;-----------------------------------------------------------------------------
ANFANG proc
        push @DATA           
        pop ds                  ; Datensegment laden

        mov ax, 12h
        int 10h                 ; Bildschrim auf 640x480 16Farben stellen

        lea dx, HalloMSG
        mov ah, 09h
        int 21h                 ; Text aus *dx ausgeben

    ;-------------------------------------------------------------------------
    ; Die Maus-Prozedurien einstellen:
    ;-------------------------------------------------------------------------
    ;   -> fuer die linke Taste:
    ;-------------------------------------------------------------------------
        mov ax, 0Ch
        mov cx, 4
        push @CODE
        pop es
        mov dx, OFFSET MAUSPROZEDUR_LINKS
        int 33h

    ;-------------------------------------------------------------------------
    ;   -> fuer die rechte Taste:
    ;-------------------------------------------------------------------------
        mov ax, 0Ch
        mov cx, 16
        push @CODE
        pop es
        mov dx, OFFSET MAUSPROZEDUR_RECHTS
        int 33h

    ;-------------------------------------------------------------------------
    ; Maus-Cursor aktivieren
    ;-------------------------------------------------------------------------
        mov ax, 1
        int 33h

    ;-------------------------------------------------------------------------
    ; Eine Schleife zur Tastenabfrage. Bei ESC wird das Programm beendet.
    ;-------------------------------------------------------------------------
    CHECK_KEYS:    
        xor ax, ax
        int 16h                 ; Keyboard lesen
        cmp al, KEY_ESC         ; schauen, ob ESC gedrueckt wurde
        jne CHECK_KEYS          ; 

    ;-------------------------------------------------------------------------
    ; Das Programmende einleiten.
    ;-------------------------------------------------------------------------
        mov ax, 2h
        int 33h                 ; Maus-Cursor deaktivieren

        mov ax, 3h              
        int 10h                 ; Bildschirm wieder zuruecksetzten

        mov ah, 4Ch
        int 21h                 ; Rueckkehr zu DOS
        ret
ANFANG endp

;-----------------------------------------------------------------------------
; Freigabe der 4 Farbebenen
;-----------------------------------------------------------------------------
FARBEBENEN_FREIGEBEN proc far
        pusha
        mov dx, 3C4h
        mov al, 2h
        out dx, al
        inc dx
        mov al, 0Fh
        out dx, al
        popa
        ret
FARBEBENEN_FREIGEBEN endp

;-----------------------------------------------------------------------------
; Modus 2 fuer Farbebenen einstellen
;-----------------------------------------------------------------------------
FARBEBENEN_MODUS2 proc far
        pusha
        mov dx, 3CEh
        mov al, 5h
        out dx, al
        inc dx
        mov al, 2h
        out dx, al
        popa
        ret
FARBEBENEN_MODUS2 endp

;-----------------------------------------------------------------------------
; Gibt die Art des Steines an Position ax in ersten beiden High-Bits von ax
; zurueck.
;-----------------------------------------------------------------------------
; Parameter:
;   ax: (X,Y)
;-----------------------------------------------------------------------------
; Rueckgabe:
;   ax: Farbe
;   ax: (X,Y)
;-----------------------------------------------------------------------------
GET_STEIN_BRETT proc far
        push bx
        push cx
        push dx
        push ds
        push di
        push ax

        push @DATA
        pop ds

        shl ax, 2               ; 2 High-Bits loswerden
        shr ax, 2               ; und 2 Nullen dafuer einsetzten

        mov cx, ax
        and cx, FELDINDEX_MASKE ; 0, 1, 2 oder 3 (Position im Byte)
        shl ax, 2               ; 4 Felder pro Byte
        mov di, OFFSET Spielbrett
        add di, ax              ; benoetigtes Byte
        mov bh, ds:[ di]        ; Byte holen

        mov bl, STEIN_MASKE     ; Feld-Stein-Bitmaske setzten

        shr cx, 1
        shl bl, cl              ; um 0/2/4/6 Einheiten schieben

        and bh, bl              ; entsprechende 2 Bits erhalten

        shr bh, cl              ; wieder nach ganz vorne schieben
        
        pop ax                  ; hole Eingabe-ax
        add ah, bh              ; fuege die 2 Bits an ah vorne an

        pop di
        pop ds
        pop dx
        pop cx
        pop bx
        ret
GET_STEIN_BRETT endp

;-----------------------------------------------------------------------------
; Setzt den Stein auf das Feld. Parameter ist ax mit Stein und Ziel.
;-----------------------------------------------------------------------------
; Parameter:
;   ax: Farbe
;   ax: (X,Y)
;-----------------------------------------------------------------------------
SET_STEIN_BRETT proc far
        push ax
        push bx
        push cx
        push dx
        push ds
        push di

        push @DATA
        pop ds

        mov bx, ax
        mov cx, ax
        mov dl, STEIN_MASKE
        
        and ax, FELDNUMMER_MASKE    ; die eigentliche Feldnummer
        and bh, STEIN_MASKE     ; der eigentliche Stein
        and cx, FELDINDEX_MASKE ; die Stelle im Byte

        shl cx, 1               ; 0/2/4/6
        shr bh, cl              ; Stein an Stelle schieben        
        shr dl, cl              ; Loesch-Maske setzten
        shr ax, 2               ; Byte mit Feld waehlen

        mov di, OFFSET Spielbrett
        add di, ax              ; benoetigtes Byte mit Feld setzten

        xor dl, 11111111b       ; Loesch-Maske umdrehen

        mov bl, ds:[di]         ; aktuelles Byte mit Steinen holen
        and bl, dl              ; Stein loeschen
        or bl, bh               ; Stein setzten

        mov ds:[di], bl         ; Byte zurueckschreiben

        pop di
        pop ds
        pop dx
        pop cx
        pop bx
        pop ax
        ret
SET_STEIN_BRETT endp

;-----------------------------------------------------------------------------
; Prueft ein Feld und dessen Rundum
;-----------------------------------------------------------------------------
; Parameter:
;   ax: Farbe
;   ax: (X,Y)
;   STANDARD : Standard-Rueckgabewert
;-----------------------------------------------------------------------------
; Rueckgabe:
;   Variable RUECKGABE
;-----------------------------------------------------------------------------
CHECK_RUNDUM proc far
        push ax
        push bx
        push cx
        push ds

        push @DATA
        pop ds

        mov bx, ax
        mov cx, ax
        and ax, FELDNUMMER_MASKE
        call GET_STEIN_BRETT
        and ah, STEIN_MASKE

        cmp ah, FELD_FREI           ; falls Platz frei
        je CHANGE_RUECKGABE         ; gibt !Standard zurueck

        and ch, STEIN_MASKE
        cmp ah, ch                  ; falls Platz != Farbe
        jne CHECKRUNDUM_ENDE        ; Ende


    ;-------------------------------------------------------------------------
    ; Anpassung von X und Y
    ;-------------------------------------------------------------------------
        mov cx, bx
        mov ax, bx
        and cx, FELDNUMMER_MASKE

    ;-------------------------------------------------------------------------
    ;   (X , Y - 1) => XY >= 19         ; Pruefe oberes Feld
    ;-------------------------------------------------------------------------
        cmp cx, YPLUS
        jl cKLEINER19

        sub ax, YPLUS
        call CHECK_RUNDUM
        add ax, YPLUS

        mov bl, STANDARD
        cmp RUECKGABE, bl               ; falls RUECKGABE == !STANDARD
        jne CHECKRUNDUM_ENDE            ; Ende

    ;-------------------------------------------------------------------------
    ;   (X + 1 , Y) => XY + 1 <= 360    ; Pruefe rechtes Feld
    ;-------------------------------------------------------------------------
    cKLEINER19:
        cmp cx, XYMAX
        jge cGROESSER360X

        add ax, XPLUS
        call CHECK_RUNDUM
        sub ax, XPLUS

        mov bl, STANDARD
        cmp RUECKGABE, bl               ; falls RUECKGABE == !STANDARD
        jne CHECKRUNDUM_ENDE            ; Ende                        

    ;-------------------------------------------------------------------------
    ;   (X , Y + 1) => XY + 19 <= 360   ; Pruefe unteres Feld
    ;-------------------------------------------------------------------------
    cGROESSER360X:    
        cmp cx, XYMAX - YPLUS
        jg cGROESSER360Y

        add ax, YPLUS
        call CHECK_RUNDUM
        sub ax, YPLUS

        mov bl, STANDARD
        cmp RUECKGABE, bl               ; falls RUECKGABE == !STANDARD
        jne CHECKRUNDUM_ENDE            ; Ende                        

    ;-------------------------------------------------------------------------
    ;   (X - 1 , Y) => XY >= 1          ; Pruefe linkes Feld
    ;-------------------------------------------------------------------------
    cGROESSER360Y:
        cmp cx, XPLUS
        jl CHECKRUNDUM_ENDE

        sub ax, XPLUS
        call CHECK_RUNDUM
        add ax, XPLUS
        jmp CHECKRUNDUM_ENDE

    CHANGE_RUECKGABE:
        mov al, STANDARD 
        not al                          ; 0 => -1 , -1 => 0
        mov RUECKGABE, al           

    CHECKRUNDUM_ENDE:

        pop ds
        pop cx
        pop bx
        pop ax
        ret
CHECK_RUNDUM endp

;-----------------------------------------------------------------------------
; Entfernt Steine und gibt Anzahl der Entfernten zurueck
;-----------------------------------------------------------------------------
; Parameter:
;   ax: Farbe
;   ax: (X,Y)
;-----------------------------------------------------------------------------
; Rueckgabe:
;   Variable ANZAHL
;-----------------------------------------------------------------------------
ENTFERNE proc far
        push ax
        push bx
        push cx
        push ds

        mov bx, ax
        mov cx, ax
        and ax, FELDNUMMER_MASKE
        call GET_STEIN_BRETT
        and ah, STEIN_MASKE

        and ch, STEIN_MASKE
        cmp ah, ch                  ; wenn Platz(X,Y) == Farbe
        jne ENTFERNE_ENDE           ; nein -> Ende
        cmp ah, FELD_FREI           ; wenn Platz(X,Y) == Frei
        je ENTFERNE_ENDE            ; ja -> Ende

        inc ANZAHL                  ; ein Punkt mehr

        mov ax, bx
        and ax, FELDNUMMER_MASKE
        call SET_STEIN_BRETT        ; mache Feld frei

    ;-------------------------------------------------------------------------
    ; Anpassung von X und Y
    ;-------------------------------------------------------------------------
        mov cx, bx
        mov ax, bx
        and cx, FELDNUMMER_MASKE

    ;-------------------------------------------------------------------------
    ;   (X , Y - 1) => XY >= 19         ; Pruefe oberes Feld
    ;-------------------------------------------------------------------------
        cmp cx, YPLUS
        jl eKLEINER19

        sub ax, YPLUS
        call ENTFERNE
        add ax, YPLUS

    ;-------------------------------------------------------------------------
    ;   (X + 1 , Y) => XY + 1 <= 360    ; Pruefe rechtes Feld
    ;-------------------------------------------------------------------------
    eKLEINER19:
        cmp cx, XYMAX
        jge eGROESSER360X

        add ax, XPLUS
        call ENTFERNE
        sub ax, XPLUS

    ;-------------------------------------------------------------------------
    ;   (X , Y + 1) => XY + 19 <= 360   ; Pruefe unteres Feld
    ;-------------------------------------------------------------------------
    eGROESSER360X:    
        cmp cx, XYMAX - YPLUS
        jg eGROESSER360Y

        add ax, YPLUS
        call ENTFERNE
        sub ax, YPLUS

    ;-------------------------------------------------------------------------
    ;   (X - 1 , Y) => XY >= 1          ; Pruefe linkes Feld
    ;-------------------------------------------------------------------------
    eGROESSER360Y:
        cmp cx, XPLUS
        jl ENTFERNE_ENDE

        sub ax, XPLUS
        call ENTFERNE
        add ax, XPLUS

    ENTFERNE_ENDE:
        pop ds
        pop cx
        pop bx
        pop ax
        ret
ENTFERNE endp

;-----------------------------------------------------------------------------
; Prueft ein Feld und dessen Rundum
;-----------------------------------------------------------------------------
; Parameter:
;   ax: Farbe
;   ax: (X,Y)
;-----------------------------------------------------------------------------
; Rueckgabe:
;   Variable RUECKGABE
;-----------------------------------------------------------------------------
PRUEFE proc far
        push ax
        push bx
        push cx
        push ds

        push @DATA
        pop ds

        mov bx, ax
        and ax, FELDNUMMER_MASKE    

        call GET_STEIN_BRETT        
        and ah, STEIN_MASKE         
        cmp ah, FELD_FREI           ; Ist Platz noch frei?
        jne pNICHT_FREI             ; nein -> weiter forschen

        mov RUECKGABE, TRUE
        jmp PRUEFE_ENDE

    pNICHT_FREI:
        mov cx, bx
        and ch, STEIN_MASKE         ; Farbe des Steins
        cmp ah, ch
        sete STANDARD               ; gleich -> 1, sonst 0
        dec STANDARD                ; 1->FALSE , 0->TRUE

        mov ax, bx
        call CHECK_RUNDUM

        cmp RUECKGABE, TRUE         ; War Check erfolgreich?
        jne PRUEFE_ENDE             ; nein -> Ende

        mov ANZAHL, 0
        call ENTFERNE               ; entferne Stein
        
        xor ax, ax
        add ax, ANZAHL              

        cmp ch, FELD_SCHWARZ
        jne PLUS_WEISS
        add ax, PUNKTE_SCHWARZ      ; Punkte zu Schwarz addieren
        mov PUNKTE_SCHWARZ, ax
        jmp PRUEFE_ENDE

    PLUS_WEISS:
        add ax, PUNKTE_WEISS        ; Punkte zu Weiss addieren
        mov PUNKTE_WEISS, ax

    PRUEFE_ENDE:
        pop ds
        pop cx
        pop bx
        pop ax
        ret
PRUEFE endp

;-----------------------------------------------------------------------------
; Pruefe um das zu setztende Feld, ob Setzten moeglich ist
;-----------------------------------------------------------------------------
; Parameter:
;   ax: Farbe
;   ax: (X,Y)
;-----------------------------------------------------------------------------
; Rueckgabe:
;   Variable RUECKGABE
;-----------------------------------------------------------------------------
PRUEFE_RUNDUM proc far
        push ax
        push bx
        push cx
        push ds

        push @DATA
        pop ds
        
        mov RUECKGABE, 0
        xor bx, bx
    ;-------------------------------------------------------------------------
    ; Anpassung von X und Y
    ;-------------------------------------------------------------------------
        mov cx, ax
        and cx, FELDNUMMER_MASKE

    ;-------------------------------------------------------------------------
    ;   (X , Y - 1) => XY >= 19         ; Pruefe oberes Feld                  
    ;-------------------------------------------------------------------------
        cmp cx, YPLUS                                                         
        jl pKLEINER19                                                         
                                                                              
        sub ax, YPLUS                                                         
        call PRUEFE                                                           
        add ax, YPLUS                                                         
        or bl, RUECKGABE                                                      
                                        
    ;-------------------------------------------------------------------------
    ;   (X + 1 , Y) => XY + 1 <= 360    ; Pruefe rechtes Feld                 
    ;-------------------------------------------------------------------------
    pKLEINER19:                                                               
        cmp cx, XYMAX                                                         
        jge pGROESSER360X                                                     
                                                                              
        add ax, XPLUS                                                         
        call PRUEFE                                                           
        sub ax, XPLUS                                                         
        or bl, RUECKGABE                
                                        
    ;-------------------------------------------------------------------------
    ;   (X , Y + 1) => XY + 19 <= 360   ; Pruefe unteres Feld
    ;-------------------------------------------------------------------------
    pGROESSER360X:                                                            
        cmp cx, XYMAX - YPLUS                                                 
        jg pGROESSER360Y                                                      
                                                                              
        add ax, YPLUS                                                         
        call PRUEFE                                                           
        sub ax, YPLUS                   
        or bl, RUECKGABE                
                                        
    ;-------------------------------------------------------------------------
    ;   (X - 1 , Y) => XY >= 1          ; Pruefe linkes Feld                  
    ;-------------------------------------------------------------------------
    pGROESSER360Y:
        cmp cx, XPLUS
        jl pKLEINER1

        sub ax, XPLUS
        call PRUEFE
        add ax, XPLUS
        or bl, RUECKGABE

    pKLEINER1:
        mov RUECKGABE, bl

        pop ds
        pop cx
        pop bx
        pop ax
        ret
PRUEFE_RUNDUM endp

;-----------------------------------------------------------------------------
; Versuchen den Stein zu setzten
;-----------------------------------------------------------------------------
; Parameter:
;   ax : Farbe
;   ax : (X,Y)
;-----------------------------------------------------------------------------
SETZTE_STEIN proc far
        push ax
        push cx
        push ds
        
        mov cx, ax

        push @DATA
        pop ds

        and ax, FELDNUMMER_MASKE    ; Steinposition
        call GET_STEIN_BRETT        ; hole Farbe von Stein an Position
        and ah, STEIN_MASKE         ;
        cmp ah, FELD_FREI           ; Ist Feld noch frei ?
        jne ENDE_SETZTE_STEIN       ; Nein -> Ende

        mov ax, cx
        call SET_STEIN_BRETT        ; Setzte Stein
        call PRUEFE_RUNDUM          ; Pruefe Rundum
        cmp RUECKGABE, TRUE         ; war es ok?
        je ENDE_SETZTE_STEIN        ; ja -> Ende

        and ax, FELDNUMMER_MASKE    ; FREI fuer Feld setzten
        call SET_STEIN_BRETT        ; Feld wieder frei machen

    ENDE_SETZTE_STEIN:
        pop ds
        pop cx
        pop ax
        ret
SETZTE_STEIN endp

;-----------------------------------------------------------------------------
; Behandlung der linken Maustaste
;-----------------------------------------------------------------------------
MAUSPROZEDUR_LINKS proc far
        pusha
; cx -> x
; dx -> y
        popa
        ret
MAUSPROZEDUR_LINKS endp

;-----------------------------------------------------------------------------
; Behandlung der rechten Maustaste
;-----------------------------------------------------------------------------
MAUSPROZEDUR_RECHTS proc far
        pusha

        popa
        ret
MAUSPROZEDUR_RECHTS endp


;-----------------------------------------------------------------------------
; Das Programmende.
;-----------------------------------------------------------------------------
end ANFANG
