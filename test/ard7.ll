; ModuleID = 'main_mod'

define i16 @main() {
entry:
  call void @init()
  %0 = call i16 @analogRead(i8 0)
  %cmpi = icmp sgt i16 %0, 10
  br i1 %cmpi, label %if_then, label %if_cont

if_then:                                          ; preds = %entry
  call void @analogWrite(i8 3, i16 255)
  br label %if_cont

if_cont:                                          ; preds = %entry, %if_then
  %i = alloca i16, align 2
  store i16 0, i16* %i, align 2
  br label %while_cond

while_cond:                                       ; preds = %while_body, %if_cont
  %i3 = phi i16 [ %1, %while_body ], [ 0, %if_cont ]
  %cmpi2 = icmp slt i16 %i3, 200
  br i1 %cmpi2, label %while_body, label %while_end

while_body:                                       ; preds = %while_cond
  %1 = add i16 %i3, 20
  store i16 %1, i16* %i, align 2
  call void @analogWrite(i8 3, i16 0)
  call void @delay(i32 100)
  call void @analogWrite(i8 3, i16 %1)
  call void @delay(i32 500)
  br label %while_cond

while_end:                                        ; preds = %while_cond
  %2 = call i16 @analogRead(i8 1)
  %cmpi6 = icmp sgt i16 %2, 10
  br i1 %cmpi6, label %if_then7, label %if_else8

if_then7:                                         ; preds = %while_end
  call void @analogWrite(i8 6, i16 255)
  br label %if_cont9

if_else8:                                         ; preds = %while_end
  call void @analogWrite(i8 6, i16 0)
  br label %if_cont9

if_cont9:                                         ; preds = %if_else8, %if_then7
  ret i16 0
}

declare i16 @analogRead(i8)

declare void @analogWrite(i8, i16)

declare void @delay(i32)

declare void @init()
