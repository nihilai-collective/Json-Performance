
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 552.232 | 0.228616 | 326.607ms | 1811 | 40 | 2044.87 | 3127.5 | 0.0266525 | 5.44104 | 1(Win) | true |
| Glaze | 437.268 | 0.109913 | 416.139ms | 1798 | 1280 | 23779.1 | 3921.41 | 0.0199187 | 6.91638 | 2(Loss) | true |
