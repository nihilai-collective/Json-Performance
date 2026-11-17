
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 813.645 | 0.0509238 | 222.318ms | 1811 | 40 | 46.7378 | 2122.68 | 0.0231572 | 3.0069 | 1(Win) | true |
| simdjson (reflection) | 568.165 | 0.0291391 | 345.773ms | 1997 | 30 | 28.6207 | 3352 | 0.109507 | 4.3198 | 2(Loss) | true |
| Glaze | 522.663 | 0.17075 | 337.45ms | 1798 | 4890 | 153450 | 3280.71 | 0.28568 | 4.69741 | 3(Loss) | true |
