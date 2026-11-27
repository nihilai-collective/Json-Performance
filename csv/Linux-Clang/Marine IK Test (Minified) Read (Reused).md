
----
### Marine IK Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 649.669 | 0.0846388 | 9203.19ms | 1834197 | 80 | 4.15467e+08 | 2.69249e+06 | 0.582675 | 7.83438 | 32.2077 | 6.69674 | 0.0416021 | 0.117952 | 0.00488903 | 1(Win) | true |
| simdjson (ondemand) | 642.113 | 0.0828096 | 9165.06ms | 1834197 | 160 | 8.14236e+08 | 2.72417e+06 | 0.197859 | 7.87433 | 33.8585 | 5.58498 | 0.0369998 | 0.118659 | 0.00710261 | 2(Loss) | true |
