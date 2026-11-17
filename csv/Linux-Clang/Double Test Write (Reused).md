
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 807.785 | 0.050557 | 226.72ms | 1811 | 40 | 46.7378 | 2138.07 | 0.0775019 | 3.02637 | 1(Win) | true |
| Glaze | 528.612 | 0.206613 | 334.416ms | 1798 | 4890 | 219649 | 3243.79 | 0.225215 | 4.64407 | 2(Loss) | true |
