
----
### Github Events Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2672.18 | 0.0772989 | 80.4556ms | 2158 | 160 | 56.7072 | 770.169 | 0.080275 | 0.895783 | 1(Win) | true |
| Jsonifier (two-stage) | 2384.91 | 0.122694 | 89.5923ms | 2158 | 80 | 89.6796 | 862.938 | 0.163418 | 1.00701 | 2(Loss) | true |
| Glaze | 2070.45 | 0.0950374 | 101.253ms | 2158 | 80 | 71.3924 | 994 | 0.0301902 | 1.16602 | 3(Loss) | true |
| simdjson (ondemand) | 1809.22 | 0.0916286 | 123.973ms | 2158 | 80 | 86.9108 | 1137.53 | 0.127307 | 1.33551 | 4(Loss) | true |
