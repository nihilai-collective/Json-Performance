
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 288.615 | 0.129624 | 610.141ms | 1811 | 4890 | 294224 | 5984.12 | 0.400677 | 8.53887 | 1(Win) | true |
| Glaze | 208.144 | 0.188487 | 833.571ms | 1798 | 2560 | 617245 | 8238.1 | 0.08168 | 11.8549 | 2(Loss) | true |
