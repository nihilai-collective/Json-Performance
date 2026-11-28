
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 701.117 | 0.102239 | 539.069ms | 4215 | 30 | 1030.78 | 5733.33 | 0.412743 | 1(Win) | true |
| Glaze | 493.343 | 0.775144 | 863.106ms | 4215 | 40 | 159559 | 8147.95 | 0.718701 | 2(Loss) | true |
