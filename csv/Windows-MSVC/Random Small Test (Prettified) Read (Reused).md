
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1275.69 | 0.098444 | 757.27ms | 8051 | 80 | 2808.54 | 6018.75 | 0.434243 | 1.93054 | 1(Win) | true |
| Jsonifier | 1169.54 | 0.149862 | 799.248ms | 8051 | 40 | 3871.79 | 6565 | 0.0761035 | 2.10805 | 2(Loss) | true |
| Glaze | 1097.77 | 0.214026 | 824.435ms | 8051 | 2560 | 573647 | 6994.18 | 0.257919 | 2.24636 | 3(Loss) | true |
| simdjson (ondemand) | 865.009 | 0.100694 | 1021.92ms | 8051 | 80 | 6390.82 | 8876.25 | 0.0422297 | 2.85548 | 4(Loss) | true |
