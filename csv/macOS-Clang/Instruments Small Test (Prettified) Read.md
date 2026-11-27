
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3025.2 | 0.0697339 | 254.605ms | 7932 | 80 | 243.24 | 2500.51 | 0.0624482 | 1(Win) | true |
| Jsonifier (two-stage) | 2684.64 | 0.0887833 | 297.513ms | 7932 | 80 | 500.663 | 2817.71 | 0.0731441 | 2(Loss) | true |
| Glaze | 1706.31 | 0.29285 | 446.819ms | 7932 | 40 | 6742.15 | 4433.27 | 0.0295204 | 3(Loss) | true |
| simdjson (ondemand) | 1032.7 | 0.110334 | 743ms | 7932 | 30 | 1959.55 | 7325.03 | 0.0181991 | 4(Loss) | true |
