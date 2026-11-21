
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 355.819 | 0.0455939 | 523.451ms | 1997 | 30 | 178.662 | 5352.4 | 0.180279 | 6.92754 | 1(Win) | true |
| Glaze | 270.626 | 0.119666 | 646.843ms | 1798 | 4890 | 281122 | 6336.08 | 0.0222112 | 9.11181 | 2(Loss) | true |
