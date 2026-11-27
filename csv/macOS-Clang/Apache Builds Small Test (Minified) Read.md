
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1601.1 | 0.0766511 | 171.55ms | 2632 | 320 | 462.085 | 1567.72 | 0.0672209 | 1(Win) | true |
| Jsonifier (two-stage) | 1397.71 | 0.140426 | 214.753ms | 2632 | 40 | 254.387 | 1795.85 | 0.00278427 | 2(Loss) | true |
| Glaze | 918.482 | 0.198828 | 275.065ms | 2632 | 4890 | 144377 | 2732.85 | 0.371504 | 3(Loss) | true |
| simdjson (ondemand) | 678.714 | 0.51841 | 329.291ms | 2632 | 640 | 235247 | 3698.28 | 0.560574 | 4(Loss) | true |
