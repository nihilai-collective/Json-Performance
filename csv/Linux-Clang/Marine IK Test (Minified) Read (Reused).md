
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 948.934 | 0.102623 | 6470.75ms | 1834197 | 40 | 1.43143e+08 | 1.84336e+06 | 0.26293 | 5.31957 | 23.559 | 4.94008 | 0.0302794 | 0.0561369 | 0.000378572 | 1(Win) | true |
| Jsonifier (two-stage) | 807.913 | 0.437065 | 7570.44ms | 1834197 | 30 | 2.68644e+09 | 2.16512e+06 | 0.575955 | 6.24678 | 27.604 | 5.49183 | 0.035715 | 0.120273 | 0.000295043 | 2(Loss) | true |
| Glaze | 731.746 | 0.0613815 | 8191.07ms | 1834197 | 160 | 3.44482e+08 | 2.39048e+06 | 0.222726 | 6.89562 | 28.993 | 5.79232 | 0.0343368 | 0.0586249 | 0.000980991 | 3(Loss) | true |
| simdjson (ondemand) | 625.116 | 0.533371 | 9547.14ms | 1834197 | 30 | 6.68268e+09 | 2.79824e+06 | 0.432587 | 8.0694 | 34.223 | 5.59901 | 0.0411475 | 0.119028 | 0.000610403 | 4(Loss) | true |
