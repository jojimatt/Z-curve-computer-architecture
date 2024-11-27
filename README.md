# Z-curve-computer-architecture
This is a group project completely done with c which creates an svg file with Z-curve for any given diagram. The code has one basic implementations and further three optimized version implementations which runs faster using methods like SIMD.

Use command make to compile the program <br>
Then run: ./main -options

-d\<int>    : o give a degree >=1 <br>
-V<int>    : select implemenation version <br>
		0:Main Implementation(simd version 1)(z_curve)<br>
		1:Simd (version 2) implementation(z_curve_V1)<br>
		2:Bitmask implementation(z_curve_V2)<br>
 		3:First and basic implementation(z_curve_V3)<br>
		If option not set main Implementation selected(For eg. ./main -d<int> calls main Implementation).<br>
		z_curve_at has only two implementations and z_curve_pos has 3<br>
-B\<int>    : number of repetitions for testing <br>
-h,--help  : help <br>
-i\<int>    :To set index and call z_curve_at <br>
-p         : use this to call z_curve_pos <br>
\<int> \<int>: to give coordinates for z_curve_pos funciton
