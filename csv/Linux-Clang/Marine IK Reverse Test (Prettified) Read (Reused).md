
----
### Marine IK Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1426.59 | 0.197115 | 7885.97ms | 7351818 | 80 | 7.50796e+09 | 4.9147e+06 | 0.94452 | 3.54801 | 15.4419 | 3.25349 | 0.0111869 | 0.181742 | 0.00209611 | 1(Win) | true |
| simdjson (ondemand) | 958.022 | 0.310974 | 5404.25ms | 7351818 | 30 | 1.55385e+10 | 7.31846e+06 | 0.105468 | 5.32148 | 26.3384 | 5.13852 | 0.00942217 | 0.430835 | 0.00531121 | 2(Loss) | true |
