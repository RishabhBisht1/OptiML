; ModuleID = '1.c'
source_filename = "1.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [15 x i8] c"Factorial: %d\0A\00", align 1

; Function Attrs: nofree norecurse nosync nounwind memory(none) uwtable
define dso_local i32 @factorial(i32 noundef %0) local_unnamed_addr #0 {
  %2 = icmp slt i32 %0, 2
  br i1 %2, label %36, label %3

3:                                                ; preds = %1
  %4 = add nsw i32 %0, -1
  %5 = icmp ult i32 %0, 9
  br i1 %5, label %27, label %6

6:                                                ; preds = %3
  %7 = and i32 %4, -8
  %8 = sub i32 %0, %7
  %9 = insertelement <4 x i32> poison, i32 %0, i64 0
  %10 = shufflevector <4 x i32> %9, <4 x i32> poison, <4 x i32> zeroinitializer
  %11 = add nsw <4 x i32> %10, <i32 0, i32 -1, i32 -2, i32 -3>
  br label %12

12:                                               ; preds = %12, %6
  %13 = phi i32 [ 0, %6 ], [ %20, %12 ]
  %14 = phi <4 x i32> [ %11, %6 ], [ %21, %12 ]
  %15 = phi <4 x i32> [ <i32 1, i32 1, i32 1, i32 1>, %6 ], [ %18, %12 ]
  %16 = phi <4 x i32> [ <i32 1, i32 1, i32 1, i32 1>, %6 ], [ %19, %12 ]
  %17 = add <4 x i32> %14, <i32 -4, i32 -4, i32 -4, i32 -4>
  %18 = mul <4 x i32> %14, %15
  %19 = mul <4 x i32> %17, %16
  %20 = add nuw i32 %13, 8
  %21 = add <4 x i32> %14, <i32 -8, i32 -8, i32 -8, i32 -8>
  %22 = icmp eq i32 %20, %7
  br i1 %22, label %23, label %12, !llvm.loop !5

23:                                               ; preds = %12
  %24 = mul <4 x i32> %19, %18
  %25 = tail call i32 @llvm.vector.reduce.mul.v4i32(<4 x i32> %24)
  %26 = icmp eq i32 %4, %7
  br i1 %26, label %36, label %27

27:                                               ; preds = %3, %23
  %28 = phi i32 [ %0, %3 ], [ %8, %23 ]
  %29 = phi i32 [ 1, %3 ], [ %25, %23 ]
  br label %30

30:                                               ; preds = %27, %30
  %31 = phi i32 [ %33, %30 ], [ %28, %27 ]
  %32 = phi i32 [ %34, %30 ], [ %29, %27 ]
  %33 = add nsw i32 %31, -1
  %34 = mul nsw i32 %31, %32
  %35 = icmp ult i32 %31, 3
  br i1 %35, label %36, label %30, !llvm.loop !8

36:                                               ; preds = %30, %23, %1
  %37 = phi i32 [ 1, %1 ], [ %25, %23 ], [ %34, %30 ]
  ret i32 %37
}

; Function Attrs: nofree nounwind uwtable
define dso_local noundef i32 @main() local_unnamed_addr #1 {
  %1 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str, i32 noundef 120)
  ret i32 0
}

; Function Attrs: nofree nounwind
declare noundef i32 @printf(ptr nocapture noundef readonly, ...) local_unnamed_addr #2

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i32 @llvm.vector.reduce.mul.v4i32(<4 x i32>) #3

attributes #0 = { nofree norecurse nosync nounwind memory(none) uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nounwind uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"Ubuntu clang version 18.1.3 (1ubuntu1)"}
!5 = distinct !{!5, !6, !7}
!6 = !{!"llvm.loop.isvectorized", i32 1}
!7 = !{!"llvm.loop.unroll.runtime.disable"}
!8 = distinct !{!8, !7, !6}
