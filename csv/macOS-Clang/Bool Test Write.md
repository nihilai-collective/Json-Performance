
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1018.52 | 0.231612 | 87.8259ms | 905 | 4890 | 18836.1 | 847.382 | 0.00792924 | 1(Win) | true |
| Glaze | 132.357 | 0.125593 | 660.956ms | 905 | 40 | 2682.87 | 6520.82 | 0.0210818 | 2(Loss) | true |
