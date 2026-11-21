
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3444.05 | 0.0556247 | 99.6385ms | 3370 | 160 | 43.1097 | 933.169 | 0.0837903 | 0.697962 | 1(Win) | true |
| Glaze | 2741.05 | 0.0922348 | 125.447ms | 3370 | 30 | 35.0862 | 1172.5 | 0.031282 | 0.8836 | 2(Loss) | true |
| Jsonifier | 2562.24 | 0.0849394 | 135.547ms | 3370 | 40 | 45.4045 | 1254.33 | 0.080324 | 0.94638 | 3(Loss) | true |
| simdjson (ondemand) | 2179.52 | 0.094565 | 158.024ms | 3370 | 160 | 311.113 | 1474.58 | 0.146442 | 1.11581 | 4(Loss) | true |
