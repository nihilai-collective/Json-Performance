
----
### Twitter Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1084.27 | 0.0822121 | 1061.97ms | 3770 | 80 | 594.526 | 3315.93 | 0.0263808 | 4.81079 | 19.9851 | 3.69549 | 0.00109748 | 3.31565e-05 | 9.94695e-06 | 1(Win) | true |
| simdjson (ondemand) | 476.982 | 0.108726 | 1489.45ms | 3770 | 320 | 21493.1 | 7537.71 | 0.0348957 | 10.8493 | 49.3645 | 8.42228 | 0.0111887 | 2.65252e-05 | 3.31565e-06 | 2(Loss) | true |
