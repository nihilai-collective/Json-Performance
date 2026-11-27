
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2567.87 | 0.0676977 | 8514.64ms | 7351818 | 160 | 5.46653e+08 | 2.73037e+06 | 0.137326 | 1.96475 | 8.237 | 1.57998 | 0.0124008 | 0.0616849 | 0.00157642 | 1(Win) | true |
| Jsonifier | 2547.31 | 0.0732182 | 8577ms | 7351818 | 160 | 6.49807e+08 | 2.75241e+06 | 0.0400028 | 1.9801 | 8.24901 | 1.86881 | 0.00911988 | 0.0342127 | 0.000420144 | 2(Loss) | true |
| simdjson (reflection) | 2399.64 | 0.111698 | 9096.81ms | 7351818 | 160 | 1.70416e+09 | 2.92179e+06 | 0.0359375 | 2.09982 | 9.07273 | 1.53412 | 0.00780033 | 0.05869 | 0.000843031 | 3(Loss) | true |
| Glaze STATISTICAL TIE | 2045.01 | 0.0858385 | 5155.65ms | 7351818 | 80 | 6.92869e+08 | 3.42845e+06 | 0.0265144 | 2.46978 | 11.2349 | 2.23756 | 0.0091086 | 0.0339795 | 0.0002357 | 4(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2044.07 | 0.189232 | 5172.63ms | 7351818 | 30 | 1.26388e+09 | 3.43003e+06 | 0.317622 | 2.46711 | 10.2389 | 1.82144 | 0.00908031 | 0.0617395 | 0.000945249 | 4(Tie) | true |
