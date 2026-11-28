
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1086.39 | 0.108138 | 345.832ms | 4215 | 40 | 640.379 | 3700.07 | 0.342831 | 1(Win) | true |
| Glaze | 798.296 | 0.127579 | 477.291ms | 4215 | 40 | 1650.76 | 5035.4 | 0.124958 | 2(Loss) | true |
| simdjson (ondemand) | 706.796 | 0.145251 | 573.783ms | 4215 | 4890 | 333698 | 5687.27 | 0.159623 | 3(Loss) | true |
