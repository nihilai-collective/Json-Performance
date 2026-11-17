
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1879.94 | 0.237727 | 10074.4ms | 5373214 | 30 | 1.25968e+09 | 2.72578e+06 | 0.193385 | 1.31693 | 1(Win) | true |
| Jsonifier | 1836.66 | 0.174562 | 10215.5ms | 5373214 | 40 | 9.48789e+08 | 2.79001e+06 | 0.224536 | 1.34797 | 2(Loss) | true |
| simdjson (ondemand) | 1802.17 | 0.247334 | 5033.41ms | 5373214 | 80 | 3.9567e+09 | 2.8434e+06 | 0.637848 | 1.37372 | 3(Loss) | true |
| Glaze | 1710.51 | 0.112979 | 5330.55ms | 5373214 | 40 | 4.58214e+08 | 2.99577e+06 | 0.804985 | 1.44739 | 4(Loss) | true |
