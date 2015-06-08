; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  br label %while_cond

while_cond:                                       ; preds = %while_body, %entry
  %0 = call i16 @analogRead(i8 0)
  %cmpi = icmp sgt i16 %0, 10
  br i1 %cmpi, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  %1 = call i16 @analogRead(i8 1)
  br label %while_cond

while_end:                                        ; preds = %while_cond
  call void @analogWrite(i8 6, i16 10)
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
