
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2808.91 | 0.084158 | 7752.58ms | 7351818 | 80 | 3.53017e+08 | 2.49607e+06 | 0.192477 | 0.881392 | 1(Win) | true |
| Jsonifier | 2623.17 | 0.0882834 | 8287.68ms | 7351818 | 40 | 2.22718e+08 | 2.67281e+06 | 0.068345 | 0.943811 | 2(Loss) | true |
| simdjson (ondemand) | 2237.59 | 0.102846 | 9817.54ms | 7351818 | 30 | 3.11546e+08 | 3.13339e+06 | 0.439861 | 1.10644 | 3(Loss) | true |
| Glaze | 2146.51 | 0.0912205 | 10202.4ms | 7351818 | 160 | 1.42045e+09 | 3.26634e+06 | 0.0442099 | 1.15338 | 4(Loss) | true |
