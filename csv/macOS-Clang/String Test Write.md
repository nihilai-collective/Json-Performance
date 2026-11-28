
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 601.712 | 0.0751563 | 563.548ms | 4215 | 30 | 756.259 | 6680.5 | 0.0214509 | 1(Win) | true |
| Glaze | 503.846 | 0.0465205 | 815.13ms | 4215 | 80 | 1101.99 | 7978.1 | 0.0128493 | 2(Loss) | true |
