; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
