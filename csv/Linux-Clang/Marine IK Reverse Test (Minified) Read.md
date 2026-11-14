
----
### Marine IK Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 831.275 | 0.0825196 | 6559.01ms | 1834197 | 160 | 4.82434e+08 | 2.10427e+06 | 0.00237844 | 6.04264 | 26.9526 | 5.76305 | 0.0298908 | 0.0816069 | 0.000456412 | 1(Win) | true |
| Jsonifier (two-stage) | 721.722 | 0.175824 | 7629.31ms | 1834197 | 40 | 7.26385e+08 | 2.42368e+06 | 0.144108 | 6.91895 | 31.0105 | 6.2879 | 0.0365773 | 0.145291 | 0.000851912 | 2(Loss) | true |
| Glaze | 669.701 | 0.0832979 | 8141.8ms | 1834197 | 160 | 7.57388e+08 | 2.61195e+06 | 0.024171 | 7.50868 | 32.0054 | 6.49715 | 0.0353598 | 0.0816454 | 0.000962761 | 3(Loss) | true |
| simdjson (ondemand) | 574.528 | 0.158009 | 9570.65ms | 1834197 | 160 | 3.70298e+09 | 3.04463e+06 | 0.61893 | 8.75735 | 37.2666 | 6.30541 | 0.046048 | 0.146998 | 0.00127585 | 4(Loss) | true |
