; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  call void @analogWrite(i8 3, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 200)
  %0 = call i16 @analogRead(i8 0)
  call void @analogWrite(i8 3, i16 %0)
  %1 = call i16 @analogRead(i8 1)
  call void @analogWrite(i8 5, i16 %1)
  %2 = call i16 @analogRead(i8 2)
  call void @analogWrite(i8 6, i16 %2)
  call void @delay(i32 500)
  %3 = call i16 @analogRead(i8 0)
  call void @analogWrite(i8 3, i16 %3)
  %4 = call i16 @analogRead(i8 1)
  call void @analogWrite(i8 5, i16 %4)
  %5 = call i16 @analogRead(i8 2)
  call void @analogWrite(i8 6, i16 %5)
  call void @delay(i32 500)
  %6 = call i16 @analogRead(i8 0)
  call void @analogWrite(i8 3, i16 %6)
  %7 = call i16 @analogRead(i8 1)
  call void @analogWrite(i8 5, i16 %7)
  %8 = call i16 @analogRead(i8 2)
  call void @analogWrite(i8 6, i16 %8)
  call void @delay(i32 500)
  %9 = call i16 @analogRead(i8 0)
  call void @analogWrite(i8 3, i16 %9)
  %10 = call i16 @analogRead(i8 1)
  call void @analogWrite(i8 5, i16 %10)
  %11 = call i16 @analogRead(i8 2)
  call void @analogWrite(i8 6, i16 %11)
  call void @delay(i32 500)
  call void @analogWrite(i8 3, i16 0)
  call void @analogWrite(i8 5, i16 0)
  call void @analogWrite(i8 6, i16 0)
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
