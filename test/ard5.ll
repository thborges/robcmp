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
  call void @analogWrite(i8 6, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 6, i16 0)
  call void @delay(i32 200)
  br label %while_cond

while_end:                                        ; preds = %while_cond
  %i = alloca i16, align 2
  br label %while_cond2

while_cond2:                                      ; preds = %while_body5, %while_end
  %i8 = phi i16 [ %1, %while_body5 ], [ 0, %while_end ]
  store i16 %i8, i16* %i, align 2
  %cmpi4 = icmp slt i16 %i8, 10
  br i1 %cmpi4, label %while_body5, label %while_end9

while_body5:                                      ; preds = %while_cond2
  call void @analogWrite(i8 3, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 200)
  %1 = add i16 %i8, 1
  br label %while_cond2

while_end9:                                       ; preds = %while_cond2
  call void @analogWrite(i8 5, i16 10)
  call void @analogWrite(i8 6, i16 10)
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
