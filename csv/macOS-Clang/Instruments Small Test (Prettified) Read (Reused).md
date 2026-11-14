
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3082.94 | 0.128036 | 259.847ms | 7932 | 80 | 789.564 | 2453.68 | 0.313846 | 1(Win) | true |
| Jsonifier (two-stage) | 2784.6 | 0.0436158 | 289.191ms | 7932 | 320 | 449.238 | 2716.56 | 0.0417404 | 2(Loss) | true |
| Glaze | 1973.38 | 0.201695 | 399.364ms | 7932 | 30 | 1793.32 | 3833.3 | 0.00173912 | 3(Loss) | true |
| simdjson (ondemand) | 1101.02 | 0.142867 | 707.343ms | 7932 | 640 | 61662.8 | 6870.5 | 0.0425687 | 4(Loss) | true |
