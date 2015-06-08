; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  call void @analogWrite(i8 3, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 200)
  %0 = call i16 @analogRead(i8 0)
  %cmpf = icmp sgt i16 %0, 10
  br i1 %cmpf, label %if_then, label %if_cont

if_then:                                          ; preds = %entry
  call void @analogWrite(i8 3, i16 255)
  br label %if_cont

if_cont:                                          ; preds = %entry, %if_then
  %1 = call i16 @analogRead(i8 1)
  %cmpf2 = icmp sgt i16 %1, 10
  br i1 %cmpf2, label %if_then3, label %if_cont5

if_then3:                                         ; preds = %if_cont
  call void @analogWrite(i8 5, i16 255)
  br label %if_cont5

if_cont5:                                         ; preds = %if_cont, %if_then3
  %2 = call i16 @analogRead(i8 2)
  %cmpf6 = icmp sgt i16 %2, 11
  br i1 %cmpf6, label %if_then7, label %if_cont9

if_then7:                                         ; preds = %if_cont5
  call void @analogWrite(i8 6, i16 255)
  br label %if_cont9

if_cont9:                                         ; preds = %if_cont5, %if_then7
  call void @delay(i32 200)
  call void @analogWrite(i8 3, i16 0)
  call void @analogWrite(i8 5, i16 0)
  call void @analogWrite(i8 6, i16 0)
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
