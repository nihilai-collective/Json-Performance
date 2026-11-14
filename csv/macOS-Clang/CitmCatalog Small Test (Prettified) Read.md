
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1731.14 | 0.140864 | 332.602ms | 5839 | 40 | 821.251 | 3216.68 | 0.134117 | 1(Win) | true |
| Jsonifier (two-stage) | 1602.67 | 0.0531309 | 355.204ms | 5839 | 160 | 545.258 | 3474.51 | 0.0715416 | 2(Loss) | true |
| Glaze | 1269.32 | 0.161103 | 444.075ms | 5839 | 2560 | 127875 | 4387.01 | 0.140186 | 3(Loss) | true |
| simdjson (ondemand) | 1228.01 | 0.081171 | 461.674ms | 5839 | 160 | 2167.69 | 4534.59 | 0.0416072 | 4(Loss) | true |
