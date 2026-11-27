
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2558.9 | 0.0664249 | 8528.15ms | 7351818 | 80 | 2.64993e+08 | 2.73994e+06 | 0.0888777 | 1.97025 | 8.34819 | 1.61001 | 0.0122512 | 0.0614727 | 0.000405282 | 1(Win) | true |
| Jsonifier | 2525.83 | 0.101668 | 8619.88ms | 7351818 | 30 | 2.38931e+08 | 2.77581e+06 | 0.0165282 | 1.99315 | 8.39101 | 1.9096 | 0.00894763 | 0.0342062 | 0.000313959 | 2(Loss) | true |
| simdjson (reflection) | 2426.1 | 0.039757 | 9026.1ms | 7351818 | 80 | 1.05606e+08 | 2.88992e+06 | 0.281931 | 2.082 | 9.06163 | 1.52211 | 0.00776222 | 0.0584725 | 0.000213179 | 3(Loss) | true |
| Glaze | 2050.26 | 0.154376 | 5152.17ms | 7351818 | 40 | 1.11478e+09 | 3.41968e+06 | 0.311269 | 2.46983 | 11.2419 | 2.23985 | 0.00904533 | 0.0334381 | 0.000192711 | 4(Loss) | true |
| simdjson (ondemand) | 2002.31 | 0.0988718 | 5289.7ms | 7351818 | 40 | 4.79437e+08 | 3.50157e+06 | 0.663461 | 2.53083 | 10.3851 | 1.82505 | 0.00898796 | 0.0613758 | 0.000407613 | 5(Loss) | true |
