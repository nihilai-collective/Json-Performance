
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1167.74 | 0.141101 | 9513.92ms | 1834197 | 40 | 1.78698e+08 | 1.49796e+06 | 0.156118 | 4.34847 | 12.5781 | 0.909502 | 0.00139556 | 0.0591163 | 0.000890076 | 1(Win) | true |
| Glaze | 651.024 | 0.137172 | 8380.67ms | 1833577 | 160 | 2.172e+09 | 2.68598e+06 | 0.0650211 | 7.82778 | 16.0113 | 0.996381 | 0.00118723 | 0.0493036 | 0.00186368 | 2(Loss) | true |
