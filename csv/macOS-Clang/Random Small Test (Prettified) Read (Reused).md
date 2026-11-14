
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2134.43 | 0.115804 | 437.908ms | 8051 | 30 | 520.599 | 3597.23 | 0.00185331 | 1(Win) | true |
| Jsonifier (two-stage) | 1875.05 | 0.0652317 | 559.103ms | 8051 | 80 | 570.796 | 4094.84 | 0.0766796 | 2(Loss) | true |
| Glaze | 1504.05 | 0.199339 | 584.637ms | 8051 | 4890 | 506372 | 5104.91 | 0.0120776 | 3(Loss) | true |
| simdjson (ondemand) | 1197.88 | 0.264692 | 734.112ms | 8051 | 30 | 8635.32 | 6409.7 | 0.152141 | 4(Loss) | true |
