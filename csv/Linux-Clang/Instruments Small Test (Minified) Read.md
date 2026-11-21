
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2533.54 | 0.0848322 | 178.955ms | 4669 | 160 | 355.66 | 1757.51 | 0.176341 | 0.962412 | 1(Win) | true |
| Jsonifier (two-stage) | 2316.46 | 0.10908 | 196.896ms | 4669 | 30 | 131.89 | 1922.2 | 0.257311 | 1.05339 | 2(Loss) | true |
| Glaze | 1633.99 | 0.0819397 | 279.72ms | 4669 | 40 | 199.433 | 2725.05 | 0.014065 | 1.50086 | 3(Loss) | true |
| simdjson (ondemand) | 616.331 | 0.0577984 | 733.354ms | 4669 | 30 | 523.085 | 7224.53 | 0.119643 | 4.00308 | 4(Loss) | true |
