
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2642.37 | 0.0864432 | 80.7593ms | 2158 | 160 | 72.5264 | 778.856 | 0.0441158 | 0.906047 | 1(Win) | true |
| Glaze | 2096.17 | 0.148331 | 102.513ms | 2158 | 160 | 339.34 | 981.806 | 0.197586 | 1.14942 | 2(Loss) | true |
| Jsonifier | 1786.33 | 0.152532 | 117.272ms | 2158 | 30 | 92.6448 | 1152.1 | 0.351315 | 1.35419 | 3(Loss) | true |
| simdjson (ondemand) | 1763.4 | 0.475561 | 121.438ms | 2158 | 1280 | 39429.7 | 1167.08 | 0.0513028 | 1.37131 | 4(Loss) | true |
