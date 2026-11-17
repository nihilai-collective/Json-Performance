
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1558.44 | 0.0337227 | 1045.3ms | 5094 | 4890 | 5403.68 | 3117.23 | 0.0388875 | 3.29631 | 14.0361 | 2.40067 | 0.000773636 | 5.86519e-05 | 1.97514e-05 | 1(Win) | true |
| Jsonifier (two-stage) | 1470.57 | 0.070983 | 1062.61ms | 5094 | 1280 | 7038.27 | 3303.5 | 0.0523867 | 3.47728 | 15.0879 | 2.54496 | 0.00177798 | 7.26958e-05 | 3.03666e-05 | 2(Loss) | true |
| Glaze | 1230.51 | 0.0341053 | 1129.16ms | 5094 | 4890 | 8865.48 | 3947.98 | 0.146615 | 4.14996 | 17.4117 | 3.31547 | 0.00530413 | 6.74839e-05 | 2.16783e-05 | 3(Loss) | true |
| simdjson (reflection) | 1059.61 | 0.11009 | 1195.23ms | 5094 | 30 | 764.271 | 4584.73 | 0.0152657 | 4.8162 | 16.0212 | 2.64036 | 0.00301008 | 8.50674e-05 | 4.58055e-05 | 4(Loss) | true |
| simdjson (ondemand) | 1042.43 | 0.0393414 | 1203.63ms | 5094 | 4890 | 16437.3 | 4660.28 | 0.123346 | 4.88021 | 17.3952 | 2.92599 | 0.00415008 | 0.000112326 | 5.15061e-05 | 5(Loss) | true |
