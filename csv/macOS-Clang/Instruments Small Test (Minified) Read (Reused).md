
----
### Instruments Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3191.19 | 0.184052 | 170.146ms | 4669 | 80 | 527.61 | 1395.31 | 0.110069 | 1(Win) | true |
| Jsonifier (two-stage) | 1985.88 | 0.0535554 | 237.082ms | 4669 | 320 | 461.42 | 2242.18 | 0.0218864 | 2(Loss) | true |
| Glaze | 1534.29 | 0.196136 | 304.44ms | 4669 | 40 | 1296.01 | 2902.12 | 0.0249879 | 3(Loss) | true |
| simdjson (ondemand) | 669.577 | 0.119969 | 681.112ms | 4669 | 2560 | 162940 | 6650.03 | 0.269987 | 4(Loss) | true |
