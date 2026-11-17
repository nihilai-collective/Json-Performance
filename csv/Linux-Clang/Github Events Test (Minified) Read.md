
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1647.06 | 0.216734 | 3077.95ms | 53331 | 1280 | 5.73334e+06 | 30879.6 | 0.300957 | 1.50172 | 1(Win) | true |
| Jsonifier | 1597.86 | 0.598991 | 3199.4ms | 53331 | 160 | 5.81627e+06 | 31830.4 | 0.610133 | 1.54802 | 2(Loss) | true |
| Glaze | 1334.15 | 0.0864782 | 3814.3ms | 53331 | 2560 | 2.78228e+06 | 38121.8 | 0.401274 | 1.85433 | 3(Loss) | true |
| simdjson (ondemand) | 989.229 | 0.0697927 | 5232.68ms | 53331 | 4890 | 6.29644e+06 | 51414.2 | 0.301863 | 2.50127 | 4(Loss) | true |
