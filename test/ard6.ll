; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  call void @analogWrite(i8 3, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 200)
  br label %while_cond

while_cond:                                       ; preds = %while_body, %entry
  %0 = call i16 @analogRead(i8 0)
  %cmpi = icmp sgt i16 %0, 10
  br i1 %cmpi, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  call void @analogWrite(i8 5, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 5, i16 0)
  call void @delay(i32 200)
  br label %while_cond

while_end:                                        ; preds = %while_cond
  %1 = call i16 @analogRead(i8 1)
  %cmpi4 = icmp sgt i16 %1, 10
  br i1 %cmpi4, label %while_cond5, label %if_cont

while_cond5:                                      ; preds = %while_end, %while_body7
  %2 = call i16 @analogRead(i8 1)
  %cmpi6 = icmp sgt i16 %2, 10
  br i1 %cmpi6, label %while_body7, label %if_cont

while_body7:                                      ; preds = %while_cond5
  call void @analogWrite(i8 6, i16 255)
  call void @delay(i32 200)
  call void @analogWrite(i8 6, i16 0)
  call void @delay(i32 200)
  br label %while_cond5

if_cont:                                          ; preds = %while_end, %while_cond5
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
