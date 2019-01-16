/*
 Copyright 2019 mirza baig

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
        limitations under the License.
*/


package com.seahawk.hello_cmake;


public class MyStructure{

    private int h;
    public int k;
    public InsideMyStructure insideMyStructure;

     public MyStructure(int param1,int param2){
        k=param1;
        h=param2;
        insideMyStructure = new InsideMyStructure(h);
     }

    public class InsideMyStructure{

         public int insidek;

         public InsideMyStructure(int param1) {
            insidek = param1;
         }
    }
}
