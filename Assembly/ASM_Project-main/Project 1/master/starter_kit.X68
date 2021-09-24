*-------------------------------------------------------
* Starting memory address for the programme $1000
*-------------------------------------------------------
    
    org $1000

*-------------------------------------------------------
*Choose to be a Plumber or a Rabbit 
*-------------------------------------------------------

*-------------------------------------------------------
*Validation values to be used, modify as needed
*Add additional validation values as required
*-------------------------------------------------------
exit        EQU 0      used to exit assembly program
min_potions EQU 1      min number of potions
max_potions EQU 5      max number of potions

min_weapons EQU 1      min weapons
max_weapons EQU 4      max weapons

win_point   EQU 5      points accumilated on win
lose_point  EQU 8      points deducted on a loss

PLAYER_HEALTH EQU 15   players health
ENEMY_HEALTH_ONE EQU 10 Enemies health
ENEMY_HEALTH_TWO EQU 10 Enemies health two
BOSS_HEALTH EQU 20      Boss health 

DAMAGE_AMOUNT EQU 2    Damage for light attack
HEAVY_DAMAGE EQU 5     Damage for the heavy attack
RABBIT_DAMAGE EQU 1    Damage for the rabbit attacks
HEALING_VALUE EQU 3    this will regen the players health 

mine_loc    EQU 100    used below for some simple collision detection using CMP
                       * example for a hit


*Start of Game
start:
    move.b  #PLAYER_HEALTH,$4000 put score/health in memory location $4000
    lea     $4000,A3   assign address A3 to that memory location
    
    move.b #ENEMY_HEALTH_ONE,$4001 putting the health of the enemy at mem location $4001
    lea $4001,A4               assign address A4 to that memory
    
    move.b #ENEMY_HEALTH_TWO,$4010 *putting the health of the enemy at mem location $4010
    lea $4010,A5
    
    move.b #BOSS_HEALTH,$4011 putting the health of the boss at mem location $4011
    lea $4011,A6

    bsr     welcome    branch to the welcome subroutine
    bsr     input      branch to the input subroutine
    bsr     game       branch to the game subroutine
*Game loop
    org     $3000      the rest of the program is to be located from 3000 onwards

*-------------------------------------------------------
*-------------------Game Subroutine---------------------
*-------------------------------------------------------
game:
    bsr     gameloop   branch to gameloop subroutine
    rts                return from game: subroutine
          
end:
    simhalt

*-------------------------------------------------------
*-------------------Welcome Subroutine------------------
*-------------------------------------------------------
welcome:
    bsr     endl            branch to endl subroutine
    lea     welcome_msg,A1  assign message to address register A1
    move.b  #14,D0          move literal 14 to DO
    trap    #15             trap and interpret value in D0
    bsr     endl            branch to endl subroutine
    rts                     return from welcome: subroutine

*-------------------------------------------------------
*---------Gameplay Input Values Subroutine--------------
*-------------------------------------------------------    
input:
    bsr     potions         branch to potion input subroutine
    bsr     weapons         branch to weaponss input subroutine
    rts

*-------------------------------------------------------
*----------------Gameloop (main loop)-------------------
*------------------------------------------------------- 
gameloop:
    bsr player_attack_select
    *bsr     update          branch to update game subroutine 
    *bsr     clear_screen    clears the screen         
    *bsr     draw            branch to draw screen subroutine
    *bsr     clear_screen    clears the screen
    *bsr     gameplay        branch to gameplay subroutine
    *bsr     clear_screen    clears the screen
    *bsr     hud             branch to display HUD subroutine
    *bsr     clear_screen    clears the screen
    *bsr     replay          branch to replay game subroutine
    *bsr     clear_screen    clears the screen
    rts                     return from gameloop: subroutine

*-------------------------------------------------------
*----------------Update Quest Progress------------------
*  Complete Quest
*------------------------------------------------------- 
update:
    bsr     endl            print a CR and LF
    bsr     decorate        decorate with dots using a loop
    lea     update_msg,A1   
    move.b  #14,D0
    trap    #15
    bsr     decorate
    rts
*-------------------------------------------------------
*-----------------Draw Quest Updates--------------------
* Draw the game progress information, status regarding
* quest
*------------------------------------------------------- 
draw:
    bsr     endl
    bsr     decorate
    lea     draw_msg,A1
    move.b  #14,D0
    trap    #15
    bsr     decorate
    rts

*-------------------------------------------------------
*--------------------Potions Inventory---------------------
* Number of potions to be used in a Quest 
*------------------------------------------------------- 
potions:
    bsr     endl
    bsr     decorate
    lea     potions_msg,A1
    move.b  #14,D0
    trap    #15
    move.b  #4,D0
    trap    #15
    move.b  max_potions,$4008
    lea     $4008,A2
    move.b  $4008,D0
    
    cmp  #5,D1
    BEQ  weapons
    *BEQ  weapons
    cmp  #5,D1
    BNE  error
   
    bsr     decorate
    rts
*------------------------------------------------------
error:
    bsr endl
    bsr decorate
    lea potionError_msg,A1
    move.b #14,D0
    trap #15
    bsr decorate
    bsr clear_screen
    bsr potions
    
*-------------------------------------------------------
*-------------------------Weapons-----------------------
* Number of weapons
*-------------------------------------------------------   
weapons:
    bsr     endl
    bsr clear_screen
    bsr     decorate
    lea     weapons_msg,A1
    move.b  #14,D0
    trap    #15
    move.b  #4,D0
    trap    #15
    bsr     decorate
    rts

*-------------------------------------------------------
*---Game Play (Quest Progress)--------------------------
*------------------------------------------------------- 
gameplay:
    bsr     endl
    bsr     decorate
    lea     gameplay_msg,A1
    move.b  #14,D0
    trap    #15
   * move.b  #4,D0
    *trap    #15
    *put  new branch here for attack
    bsr player_attack
    bsr     decorate
    *bsr     collision
    rts



*-------------------------------------------------------
*----------Rabbit Attack--------------------------------
*------------------------------------------------------- 
rabbitAttack:
    bsr endl
    bsr decorate
    lea rabbitAttack_msg,A1
    move.b #14,D0
    trap #15
    
    lea $4000,A3
    move.b $4000,D0
    
    subi.b #RABBIT_DAMAGE,D0
    
    move.b D0,$4000
    
    cmp #0,D0
    BEQ lose_screen
    
    rts


*-------------------------------------------------------
*-----------------LOSE SCREEN----------------------------
*-------------------------------------------------------   
lose_screen:
    bsr endl
    bsr decorate
    
    lea lose_screen_msg,A1
    move.b #14,D0
    trap #15
    
    simhalt
    

*-------------------------------------------------------
*-----------------Heads Up Display (Score)--------------
* Retrieves the score from memory location
*-------------------------------------------------------   
hud:

    bsr     endl
    bsr     decorate
    lea     hud_msg,A1
    move.b  #14,D0
    trap    #15
    move.b  (A3),D1     retrieve the value A3 point to and move to D1
    move.b  #3,D0       move literal 3 to D0
    trap    #15         intrepret value in D0, which 3 which displays D1
    bsr     decorate
    rts

*-------------------------------------------------------
*-----------------------Being Attacked------------------
* This could be used for collision detection
*-------------------------------------------------------
collision:
    move.b  #mine_loc,D1
    cmp     #100,D1 is( x == 100)?
	bne     collision_miss if x is equal to 100, then hit
collision_hit:
    *hit
    lea     hit_msg,A1
    move    #14,D0
    trap    #15
    rts
    
collision_miss:
    *miss
    lea     miss_msg,A1
    move    #14,D0
    trap    #15
    rts

*-------------------------------------------------------
*--------------------------Loop-------------------------
*-------------------------------------------------------
loop:
    move.b  #5, D3 loop counter D3=5
next:
    lea     loop_msg,A1
    move.b  #14,D0
    trap    #15
	sub     #1,D3   decrement loop counter
    bne     next    repeat until D0=0

*-------------------------------------------------------
*------------------Screen Decoration--------------------
*-------------------------------------------------------
decorate:
    move.b  #60, D3
    bsr     endl
out:
    lea     loop_msg,A1
    move.b  #14,D0
    trap    #15
	sub     #1,D3   decrement loop counter
    bne     out	    repeat until D0=0
    bsr     endl
    rts
    
clear_screen: 
    move.b  #11,D0      clear screen
    move.w  #$ff00,D1
    trap    #15
    rts
*-------------------------------------------------------
*------------------------Replay-------------------------
*-------------------------------------------------------
replay:
    bsr     endl
    lea     replay_msg,A1
    move.b  #14,D0
    trap    #15
    
    move.b  #4,D0
    trap    #15

    cmp     #exit,D1
    beq     end         if SR Z register contains 1 beq => Branch Equals
    bsr     gameloop

endl:
    movem.l D0/A1,-(A7)
    move    #14,D0
    lea     crlf,A1
    trap    #15
    movem.l (A7)+,D0/A1
    rts
    
*------------------------------------------------------
*--------------------ATTACK SELECTION------------------
*------------------------------------------------------
PLAYER_ATTACK_SELECT:

    *loading the player attack selection
    bsr endl
    bsr decorate
    lea PLAYER_SELECT_MSG,A1
    move.b #14,D0
    trap #15
    
    *waiting for player input 
    move.b #4,D0
    trap   #15
    move.b D0, $4005
    lea $4005,A6
    
    *now compare the value against the input, to see what weapon is picked
    cmp     #1,D1
    BEQ     PLAYER_ATTACK
   
    cmp     #2,D1
    BEQ     PLAYER_HEAVY_ATTACK

    cmp     #3,D1
    BEQ     PLAYER_HEAL
    
    bsr decorate
    bsr clear_screen
   
    RTS

*------------------------------------------------------
*-------------------------ATTACK-----------------------
*------------------------------------------------------
PLAYER_ATTACK:
    bsr  endl
    lea  player_basic_attack_msg,A1
    move.b #14,d0
    trap #15
    
    *move.b #ENEMY_HEALTH_ONE,$4002
    lea $4001,A4
    move.b $4001,d0
    
    subi.b #DAMAGE_AMOUNT,D0 
    
    move.b d0,$4001
    
    cmp #0,D0
    BEQ SECOND_ROOM
    BLT SECOND_ROOM
    
   
    
    bsr decorate
    bsr PLAYER_ATTACK_SELECT
    
    bsr rabbitAttack

*------------------------------------------------------
*--------------------HEALING THE PLAYER-----------------
*------------------------------------------------------
PLAYER_HEAL:
    bsr  endl
    bsr  decorate
    lea PLAYER_HEAL_MSG,A1
    move.b #14,D0
    trap #15
    
    *move.b  #PLAYER_HEALTH,$4000
    lea $4000,A4
    move.b  $4000,d0
    
    addi.b   #HEALING_VALUE,D0
    
    move.b D0,$4000
    *lea $4000,A4
    
 
    bsr decorate
    bsr PLAYER_ATTACK_SELECT
    
     bsr rabbitAttack
*------------------------------------------------------
*--------------------HEAVY ATTACK----------------------
*------------------------------------------------------
PLAYER_HEAVY_ATTACK:     *edit the attacks and have a rabbit attack message display to the player
    bsr   endl
    lea   PLAYER_HEAVY_MSG,A1
    move.b #14,D0
    trap   #15
    
    lea $4001,A4
    move.b $4001,d0
    
    subi.b #HEAVY_DAMAGE,d0 
    
    move.b d0,$4001
    
    cmp #0,D0
    BEQ SECOND_ROOM
    BLT SECOND_ROOM
    
   

    bsr decorate
    bsr PLAYER_ATTACK_SELECT
    
    bsr rabbitAttack
*-------------------------------------------------------
*-------------------ROOM TWO----------------------------
*-------------------------------------------------------
SECOND_ROOM:
    bsr  endl
    
    bsr clear_screen
    bsr decorate
    lea  room_two_msg,A1
    move.b #14,d0
    trap #15
    
    bsr PLAYER_ATTACK_SELECT_TWO
    
    bsr decorate
    
    
    
    
*------------------------------------------------------
*--------------------ATTACK SELECTION TWO--------------
*------------------------------------------------------
PLAYER_ATTACK_SELECT_TWO:

    *loading the player attack selection
    bsr endl
    bsr decorate
    lea weaponSelection_Two_msg,A1
    move.b #14,D0
    trap #15
    
    *waiting for player input 
    move.b #4,D0
    trap   #15
    move.b D0, $4005
    lea $4005,A6
    
    *now compare the value against the input, to see what weapon is picked
    cmp     #1,D1
    BEQ     PLAYER_ATTACK_TWO
   
    cmp     #2,D1
    BEQ     PLAYER_HEAVY_ATTACK_TWO

    cmp     #3,D1
    BEQ     PLAYER_HEAL_TWO
    
    bsr decorate
    bsr clear_screen
   
    RTS
    
*------------------------------------------------------
*---------------------BASIC ATTACK TWO----------------------
*------------------------------------------------------
PLAYER_ATTACK_TWO:
    bsr  endl
    lea  player_basic_attack_msg,A1
    move.b #14,d0
    trap #15
    
    *move.b #ENEMY_HEALTH_ONE,$4002
    lea $4010,A5
    move.b $4010,d0
    
    subi.b #DAMAGE_AMOUNT,D0 
    
    move.b d0,$4010
    
    cmp #0,D0
    BEQ boss_fight
    BLT boss_fight
    
    bsr rabbitAttack

    bsr decorate
    bsr PLAYER_ATTACK_SELECT_TWO
    
*------------------------------------------------------
*--------------------HEAVY ATTACK TWO------------------
*------------------------------------------------------
PLAYER_HEAVY_ATTACK_TWO: 
    bsr   endl
    lea   PLAYER_HEAVY_MSG,A1
    move.b #14,D0
    trap   #15
    
    lea $4010,A5
    move.b $4010,d0
    
    subi.b #HEAVY_DAMAGE,d0 
    
    move.b d0,$4010
    
    cmp #0,D0
    BEQ boss_fight
    BLT boss_fight

    bsr rabbitAttack

    bsr decorate
    bsr PLAYER_ATTACK_SELECT_TWO
    
*------------------------------------------------------
*----------------HEALING THE PLAYER TWO------------
*------------------------------------------------------
PLAYER_HEAL_TWO:
    bsr  endl
    bsr  decorate
    lea PLAYER_HEAL_MSG,A1
    move.b #14,D0
    trap #15
    
    lea $4000,A4
    move.b  $4000,d0
    
    addi.b   #HEALING_VALUE,D0
    
    move.b D0,$4000
    
    bsr rabbitAttack

    bsr decorate
    bsr PLAYER_ATTACK_SELECT_TWO
    
*-------------------------------------------------------
*-------------------BOSS FIGHT---------------------------
*-------------------------------------------------------
BOSS_FIGHT:
    bsr  endl
    
    bsr clear_screen
    bsr decorate
    lea  boss_fight_msg,A1
    move.b #14,d0
    trap #15
    
    bsr PLAYER_ATTACK_SELECT_THREE
    
    bsr decorate

*------------------------------------------------------
*---------------ATTACK SELECTION THREE--------------
*------------------------------------------------------
PLAYER_ATTACK_SELECT_THREE:

    *loading the player attack selection
    bsr endl
    bsr decorate
    lea weaponSelection_Two_msg,A1
    move.b #14,D0
    trap #15
    
    *waiting for player input 
    move.b #4,D0
    trap   #15
    move.b D0, $4005
    lea $4005,A6
    
    *now compare the value against the input, to see what weapon is picked
    cmp     #1,D1
    BEQ     PLAYER_ATTACK_THREE
   
    cmp     #2,D1
    BEQ     PLAYER_HEAVY_ATTACK_THREE

    cmp     #3,D1
    BEQ     PLAYER_HEAL_THREE
    
    bsr decorate
    bsr clear_screen
   
    RTS

*------------------------------------------------------
*---------------------BASIC ATTACK THREE----------------------
*------------------------------------------------------
PLAYER_ATTACK_THREE:
    bsr  endl
    lea  player_basic_attack_msg,A1
    move.b #14,d0
    trap #15
    
    lea $4011,A5
    move.b $4011,d0
    
    subi.b #DAMAGE_AMOUNT,D0 
    
    move.b d0,$4011
    
    cmp #0,D0
    BEQ WIN_SCREEN
    BLT boss_fight
   
    bsr rabbitAttack
    
    bsr decorate
    bsr PLAYER_ATTACK_SELECT_THREE
    
*------------------------------------------------------
*--------------------HEAVY ATTACK THREE------------------
*------------------------------------------------------
PLAYER_HEAVY_ATTACK_THREE: 
    bsr   endl
    lea   PLAYER_HEAVY_MSG,A1
    move.b #14,D0
    trap   #15
    
    lea $4011,A5
    move.b $4011,d0
    
    subi.b #HEAVY_DAMAGE,d0 
    
    move.b d0,$4011
    
    cmp #0,D0
    BEQ WIN_SCREEN
   
    bsr rabbitAttack
    
    bsr decorate
    bsr PLAYER_ATTACK_SELECT_THREE
    
*------------------------------------------------------
*----------------HEALING THE PLAYER THREE------------
*------------------------------------------------------
PLAYER_HEAL_THREE:
    bsr  endl
    bsr  decorate
    lea PLAYER_HEAL_MSG,A1
    move.b #14,D0
    trap #15
    
    lea $4000,A4
    move.b  $4000,d0
    
    addi.b   #HEALING_VALUE,D0
    
    move.b D0,$4000
    
    bsr rabbitAttack
    
    bsr decorate
    bsr PLAYER_ATTACK_SELECT_THREE
    
    
*------------------------------------------------------
*----------------HEALING THE PLAYER THREE------------
*------------------------------------------------------
WIN_SCREEN:
    bsr  endl
    
    bsr clear_screen
    bsr decorate
    lea  win_screen_msg,A1
    move.b #14,d0
    trap #15
    bsr decorate
    


*-------------------------------------------------------
*-------------------Data Delarations--------------------
*-------------------------------------------------------



crlf:           dc.b    $0D,$0A,0
welcome_msg:    dc.b    '************************************************************'
                dc.b    $0D,$0A
                dc.b    'Battle of Plumbers Vs Rabbits, Plumbers Rise Up !'
                dc.b    $0D,$0A
                dc.b    '************************************************************'
                dc.b    $0D,$0A,0
potion_msg:     dc.b    'Potion ....'
                dc.b    $0D,$0A
                dc.b    'Enter Potion : ',0
potions_msg:    dc.b    'Number of potions : ',0
weapons_msg:    dc.b    'minimum requirement is 2 i.e. Pipe Wrench x 1 and 20mm Spanner x 1.'
                dc.b    $0D,$0A
                dc.b    'Enter # of weapons : ',0
gameplay_msg:   dc.b    'Plumber, Ready your weapons there is a rabbit nearby!'
                dc.b    $0D,$0A
update_msg:     dc.b    'Update Message!'
                dc.b    $0D,$0A
draw_msg:       dc.b    'Draw Screen !',0
hit_msg:        dc.b    'Strike!',0
miss_msg:       dc.b    'Miss!',0
loop_msg:       dc.b    '.',0
replay_msg:     dc.b    'Enter 0 to Quit any other number to replay : ',0
hud_msg:        dc.b    'Score : ',0
potionError_msg dc.b    'Max potions is 5, please enter the correct amount!',0
weaponSelection_msg dc.b    'press 1 for pipe wrench, 2 for 20mm spanner and 3 for potion',0
weaponSelection_Two_msg dc.b    'press 1 for metal file, 2 for Big Boi wrench and 3 for potion',0
player_basic_attack_msg dc.b 'You have attacked the enemy and dealt 2 damage',0
                        
PLAYER_SELECT_MSG dc.b 'Press 1 for a pipe wrench, 2 for 20mm spanner or 3 for a potion',0
PLAYER_HEAL_MSG dc.b  'You have used a potion to heal, you have regained health',0
PLAYER_HEAVY_MSG dc.b 'You have chosen a heavy attack',0
room_two_msg dc.b 'Well Done Player, you defeated the enemy grunt'
             dc.b $0D,$0A
             dc.b 'Get ready player, theres another rabbit nearby'
             dc.b $0D,$0A
             dc.b 'Carefull Player, this rabbit seems more powerful than the last',0
boss_fight_msg dc.b 'This is it Player! we made it to the final boss'
               dc.b $0D,$0A
               dc.b 'if we clear out this boss this region will be free from these evil rabbits',0
win_screen_msg dc.b 'CONGRATULATIONS PLAYER!! you defeated the boss'
               dc.b $0D,$0A
               dc.b 'As a reward for your troubles, we bestow upon you the blade of olympus,'
               dc.b $0D,$0A
               dc.b 'Hylian Shield,'
               dc.b $0D,$0A
               dc.b 'golden TT'
               dc.b $0D,$0A
               dc.b 'Quadra Turbo-R 740'
               dc.b $0D,$0A
               dc.b 'finally 100,000 cold coins',0
rabbitAttack_msg dc.b 'Carefull Player, those rabbits got some big talons on em',0
lose_screen_msg dc.b 'YOU LOSE! GET GUD SCRUB',0               
health:     ds.w    1   Players Health
score:      ds.w    1   Reserve space for score

    end start









*~Font name~Courier New~
*~Font size~10~
*~Tab type~1~
*~Tab size~4~
