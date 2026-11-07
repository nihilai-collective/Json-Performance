
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2822.29 | 0.0903347 | 162.849ms | 4669 | 160 | 324.994 | 1577.69 | 0.101914 | 0.862563 | 1(Win) | true |
| Jsonifier (two-stage) | 2254.27 | 0.0907164 | 200.446ms | 4669 | 30 | 96.323 | 1975.23 | 0.147034 | 1.08384 | 2(Loss) | true |
| Glaze | 1694.73 | 0.0400862 | 267.216ms | 4669 | 160 | 177.483 | 2627.38 | 0.112167 | 1.44667 | 3(Loss) | true |
| simdjson (ondemand) | 671.193 | 0.12838 | 667.071ms | 4669 | 2560 | 185690 | 6634.02 | 0.0894031 | 3.67284 | 4(Loss) | true |
