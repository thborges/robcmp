; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  br label %while_cond

while_cond:                                       ; preds = %while_body, %entry
  %i.0 = phi i16 [ 0, %entry ], [ %1, %while_body ]
  %cmpi = icmp slt i16 %i.0, 10
  br i1 %cmpi, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  call void @analogWrite(i8 6, i16 0)
  call void @delay(i32 200)
  %0 = mul i16 %i.0, 15
  call void @analogWrite(i8 6, i16 %0)
  call void @delay(i32 500)
  %1 = add i16 %i.0, 1
  br label %while_cond

while_end:                                        ; preds = %while_cond
  call void @analogWrite(i8 3, i16 255)
  call void @analogWrite(i8 6, i16 0)
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
