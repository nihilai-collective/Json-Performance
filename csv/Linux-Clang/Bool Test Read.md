
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1770 | 0.1077 | 49.912ms | 905 | 80 | 22.0631 | 487.613 | 0.0742866 | 1.32316 | 1(Win) | true |
| Glaze | 1339.51 | 0.463856 | 67.4853ms | 905 | 4890 | 43679.6 | 644.32 | 0.99465 | 1.76854 | 2(Loss) | true |
| Jsonifier (two-stage) | 493.263 | 0.0424942 | 181.805ms | 905 | 80 | 44.2272 | 1749.72 | 0.0772146 | 4.93996 | 3(Loss) | true |
| simdjson (ondemand) | 250.672 | 0.213926 | 355.565ms | 905 | 160 | 8680.22 | 3443.04 | 0.353952 | 9.79504 | 4(Loss) | true |
