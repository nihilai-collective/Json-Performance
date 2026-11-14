
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 301.18 | 0.061894 | 587.149ms | 1811 | 40 | 503.895 | 5734.45 | 0.128588 | 1(Win) | true |
| Glaze | 223.414 | 0.0679099 | 777.932ms | 1798 | 40 | 1086.64 | 7675.02 | 0.16433 | 2(Loss) | true |
