
----
### CitmCatalog Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1956.6 | 0.127434 | 213.457ms | 3223 | 2560 | 10259.6 | 1570.93 | 0.122265 | 1(Win) | true |
| Jsonifier (two-stage) | 1382.54 | 0.0852142 | 287.294ms | 3223 | 160 | 574.264 | 2223.22 | 0.0157454 | 2(Loss) | true |
| Glaze | 1184.15 | 0.0713712 | 313.236ms | 3223 | 640 | 2196.52 | 2595.7 | 0.255419 | 3(Loss) | true |
| simdjson (ondemand) | 880.746 | 0.126969 | 399.759ms | 3223 | 160 | 3141.47 | 3489.88 | 0.0960842 | 4(Loss) | true |
