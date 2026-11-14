
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1279.5 | 0.0274637 | 8656.65ms | 1834197 | 320 | 4.51109e+07 | 1.36712e+06 | 0.00296235 | 3.94577 | 13.133 | 0.799039 | 0.00253089 | 0.0597589 | 0.000469647 | 1(Win) | true |
| Glaze | 986.741 | 0.181265 | 5525.83ms | 1833577 | 160 | 1.65097e+09 | 1.77213e+06 | 0.0229942 | 5.119 | 16.048 | 1.05269 | 0.00101142 | 0.0495565 | 5.90581e-05 | 2(Loss) | true |
| simdjson (reflection) | 884.142 | 0.016399 | 6458.3ms | 1922245 | 80 | 9.24907e+06 | 2.07342e+06 | 0.00304036 | 5.71319 | 18.1521 | 2.01847 | 0.0263056 | 0.0503143 | 3.24295e-05 | 3(Loss) | true |
