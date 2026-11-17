
----
### Random Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2025.89 | 0.0354693 | 290.55ms | 5094 | 160 | 115.747 | 2397.96 | 0.0693778 | 1.20855 | 1(Win) | true |
| Jsonifier (two-stage) | 1829.46 | 0.0260969 | 335.456ms | 5094 | 640 | 307.347 | 2655.43 | 1.24677 | 1.33883 | 2(Loss) | true |
| Glaze | 1489.42 | 0.181459 | 378.518ms | 5094 | 4890 | 171297 | 3261.67 | 0.182156 | 1.64832 | 3(Loss) | true |
| simdjson (ondemand) | 982.365 | 0.217776 | 553.537ms | 5094 | 40 | 4639.31 | 4945.23 | 0.245789 | 2.50532 | 4(Loss) | true |
