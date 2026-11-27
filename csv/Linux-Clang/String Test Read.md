
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2966.13 | 0.0353928 | 139.507ms | 4215 | 160 | 36.8099 | 1355.21 | 0.00553449 | 0.818496 | 1(Win) | true |
| simdjson (stage-1) | 2862.4 | 0.0635493 | 144.356ms | 4215 | 80 | 63.7158 | 1404.33 | 0.161738 | 0.848449 | 2(Loss) | true |
