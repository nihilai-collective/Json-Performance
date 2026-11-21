
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1260.48 | 0.212175 | 284.997ms | 3223 | 40 | 1070.77 | 2438.5 | 0.472096 | 1(Win) | true |
| Jsonifier (two-stage) | 919.276 | 0.107412 | 346.032ms | 3223 | 40 | 515.938 | 3343.6 | 0.104568 | 2(Loss) | true |
| Glaze | 713.696 | 0.288825 | 439.791ms | 3223 | 4890 | 756613 | 4306.73 | 0.0206707 | 3(Loss) | true |
| simdjson (ondemand) | 583.986 | 0.398646 | 521.647ms | 3223 | 2560 | 1.12702e+06 | 5263.29 | 1.58072 | 4(Loss) | true |
