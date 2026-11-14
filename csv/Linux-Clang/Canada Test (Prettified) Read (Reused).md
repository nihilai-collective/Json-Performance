
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2486.9 | 0.567871 | 7601.72ms | 5373214 | 40 | 5.47658e+09 | 2.06051e+06 | 0.0951068 | 1.99347 | 10.7099 | 1.77585 | 0.00441456 | 0.0522701 | 0.000725613 | 1(Win) | true |
| Jsonifier | 2337.86 | 0.0821041 | 8009.11ms | 5373214 | 160 | 5.18182e+08 | 2.19188e+06 | 0.0474331 | 2.14206 | 11.2504 | 2.31238 | 0.00299655 | 0.0280505 | 0.00202775 | 2(Loss) | true |
| simdjson (ondemand) | 2105.11 | 0.631042 | 8985.19ms | 5373214 | 30 | 7.07874e+09 | 2.43422e+06 | 0.371856 | 2.3989 | 11.7272 | 1.80438 | 0.00486158 | 0.050696 | 0.000461096 | 3(Loss) | true |
| Glaze | 1839.9 | 0.485703 | 10049.1ms | 5373214 | 30 | 5.48963e+09 | 2.78509e+06 | 0.650328 | 2.73022 | 13.9467 | 2.50128 | 0.00458118 | 0.0296887 | 0.000869368 | 4(Loss) | true |
