
----
### Twitter Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2785.39 | 0.166741 | 6164.38ms | 631514 | 160 | 2.07968e+07 | 216220 | 1.40991 | 0.888725 | 1(Win) | true |
| Glaze | 2212.95 | 0.193056 | 7994.31ms | 631514 | 80 | 2.20841e+07 | 272152 | 0.0926289 | 1.11867 | 2(Loss) | true |
| Jsonifier | 1873.05 | 0.236387 | 9283.75ms | 631514 | 80 | 4.62173e+07 | 321538 | 2.11033 | 1.32165 | 3(Loss) | true |
| simdjson (ondemand) | 1284.32 | 0.144426 | 6263.45ms | 631514 | 160 | 7.33893e+07 | 468932 | 0.691093 | 1.92756 | 4(Loss) | true |
