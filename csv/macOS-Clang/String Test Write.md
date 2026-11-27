
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 601.454 | 0.125402 | 521.43ms | 4215 | 30 | 2107.27 | 6683.37 | 0.205561 | 1(Win) | true |
| Glaze | 530.149 | 0.0652875 | 764.249ms | 4215 | 4890 | 119831 | 7582.28 | 0.0241977 | 2(Loss) | true |
