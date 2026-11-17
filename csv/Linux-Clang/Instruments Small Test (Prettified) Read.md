
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2832.44 | 0.327213 | 1005.13ms | 7932 | 2560 | 195500 | 2670.68 | 0.220966 | 1.80828 | 7.31493 | 1.18079 | 0.000664043 | 3.12717e-05 | 6.64831e-06 | 1(Win) | true |
| Glaze | 2386.37 | 0.156754 | 1057.11ms | 7932 | 4890 | 120736 | 3169.89 | 0.218281 | 2.15233 | 8.9589 | 1.6707 | 0.00147465 | 4.07348e-05 | 1.57009e-05 | 2(Loss) | true |
| Jsonifier | 2098.12 | 0.371264 | 1099.25ms | 7932 | 2560 | 458682 | 3605.4 | 0.0582229 | 2.43998 | 7.95386 | 1.78366 | 0.00136079 | 3.85109e-05 | 1.27057e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1096.56 | 0.139137 | 1429.39ms | 7932 | 2560 | 235844 | 6898.41 | 0.014062 | 4.63031 | 17.5596 | 2.72491 | 0.00172748 | 3.3931e-05 | 9.60311e-06 | 4(Loss) | true |
