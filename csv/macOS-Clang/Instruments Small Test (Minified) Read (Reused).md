
----
### Instruments Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3222.44 | 0.078754 | 163.472ms | 4669 | 320 | 378.943 | 1381.78 | 0.0190008 | 1(Win) | true |
| Jsonifier (two-stage) | 1934.46 | 0.0370367 | 246.857ms | 4669 | 640 | 465.127 | 2301.78 | 0.0130996 | 2(Loss) | true |
| Glaze | 1645.66 | 0.149723 | 285.89ms | 4669 | 2560 | 42013 | 2705.73 | 0.0359351 | 3(Loss) | true |
| simdjson (ondemand) | 669.764 | 0.0541463 | 705.802ms | 4669 | 160 | 2073.3 | 6648.18 | 0.066604 | 4(Loss) | true |
