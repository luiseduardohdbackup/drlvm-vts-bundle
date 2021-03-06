;    Copyright 2005-2006 The Apache Software Foundation or its licensors, as applicable
;
;    Licensed under the Apache License, Version 2.0 (the "License");
;    you may not use this file except in compliance with the License.
;    You may obtain a copy of the License at
;
;       http://www.apache.org/licenses/LICENSE-2.0
;
;    Unless required by applicable law or agreed to in writing, software
;    distributed under the License is distributed on an "AS IS" BASIS,
;    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;
;    See the License for the specific language governing permissions and
;    limitations under the License.

;
; Author: Alexander V. Esin
; Version: $Revision: 1.1 $
;
.class public org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301p
.super org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301super2/getfield2301super2

.method public <init>()V
   aload_0
   invokespecial org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301super2/getfield2301super2/<init>()V
   return
.end method

.method public test([Ljava/lang/String;)I
   .limit stack 2
   .limit locals 2

   aload_0
   ; putfield and getfield for protectedField field using signature of getfield2301super2 class
   sipush 104
   putfield org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301super2/getfield2301super2/protectedField I
   aload_0
   getfield org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301super2/getfield2301super2/protectedField I
   ireturn 
.end method

.method public static main([Ljava/lang/String;)V
  .limit stack 2
  .limit locals 1

  new org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301p
  dup
  invokespecial org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301p/<init>()V
  aload_0
  invokevirtual org/apache/harmony/vts/test/vm/jvms/instructions/reftypes/getfield/getfield23/getfield2301/getfield2301p/test([Ljava/lang/String;)I
  invokestatic java/lang/System/exit(I)V

  return
.end method
