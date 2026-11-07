
----
### Marine IK Small Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 977.438 | 0.0867711 | 471.879ms | 4604 | 30 | 455.789 | 4492.07 | 0.0822996 | 2.51792 | 1(Win) | true |
| Jsonifier (two-stage) | 895.031 | 0.149218 | 499.059ms | 4604 | 4890 | 262026 | 4905.66 | 0.333574 | 2.75064 | 2(Loss) | true |
| Glaze | 643.081 | 0.170162 | 686.748ms | 4604 | 80 | 10798.3 | 6827.62 | 0.200324 | 3.8342 | 3(Loss) | true |
| simdjson (ondemand) | 543.296 | 0.186971 | 821.686ms | 4604 | 1280 | 292250 | 8081.62 | 0.1134 | 4.54256 | 4(Loss) | true |
