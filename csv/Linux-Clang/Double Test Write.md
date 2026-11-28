
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 349.448 | 0.16104 | 546.002ms | 1997 | 4890 | 376675 | 5449.99 | 0.0404443 | 7.04987 | 1(Win) | true |
| Glaze | 273.15 | 0.0665831 | 646.673ms | 1798 | 40 | 698.82 | 6277.52 | 0.0110194 | 9.02656 | 2(Loss) | true |
