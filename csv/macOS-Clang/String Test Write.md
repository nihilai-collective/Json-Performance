
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1293.63 | 0.0734107 | 663.778ms | 9578 | 30 | 806.069 | 7061 | 0.0207671 | 1(Win) | true |
| Glaze | 1138.6 | 0.0412215 | 820.536ms | 9578 | 80 | 874.878 | 8022.41 | 0.083913 | 2(Loss) | true |
