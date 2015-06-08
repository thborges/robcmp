; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  call void @analogWrite(i8 3, i16 10)
  call void @analogWrite(i8 5, i16 10)
  call void @analogWrite(i8 6, i16 10)
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 500)
  call void @analogWrite(i8 3, i16 10)
  call void @delay(i32 500)
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 500)
  call void @analogWrite(i8 5, i16 10)
  call void @delay(i32 500)
  call void @analogWrite(i8 5, i16 0)
  call void @delay(i32 500)
  call void @analogWrite(i8 5, i16 10)
  call void @delay(i32 500)
  call void @analogWrite(i8 5, i16 0)
  call void @delay(i32 500)
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
