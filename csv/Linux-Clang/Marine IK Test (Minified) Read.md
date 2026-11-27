
----
### Marine IK Test (Minified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 596.238 | 0.124911 | 9162.19ms | 1834197 | 40 | 5.37174e+08 | 2.93377e+06 | 0.210192 | 8.47398 | 35.2001 | 7.39616 | 0.0427897 | 0.138753 | 0.00226307 | 1(Win) | true |
| simdjson (ondemand) | 592.932 | 0.0961823 | 9225.67ms | 1834197 | 80 | 6.44113e+08 | 2.95013e+06 | 0.369629 | 8.5346 | 36.8495 | 6.28437 | 0.038142 | 0.139274 | 0.0113123 | 2(Loss) | true |
