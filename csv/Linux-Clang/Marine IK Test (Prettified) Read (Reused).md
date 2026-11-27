
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2352.42 | 0.0964058 | 9968.56ms | 7351818 | 80 | 6.60473e+08 | 2.98043e+06 | 0.148805 | 2.14244 | 8.83612 | 1.71004 | 0.0110558 | 0.0536011 | 0.00524755 | 1(Win) | true |
| simdjson (ondemand) | 2337.88 | 0.105218 | 10076.6ms | 7351818 | 80 | 7.96552e+08 | 2.99897e+06 | 0.00168977 | 2.16333 | 9.35196 | 1.43343 | 0.00895047 | 0.0535999 | 0.00192133 | 2(Loss) | true |
