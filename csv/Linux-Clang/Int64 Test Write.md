
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 911.295 | 0.0589313 | 410.731ms | 3862 | 40 | 226.913 | 4041.6 | 0.0280338 | 2.70043 | 1(Win) | true |
| Glaze | 820.971 | 0.209063 | 455.051ms | 3862 | 1280 | 112598 | 4486.26 | 0.0215194 | 2.99849 | 2(Loss) | true |
