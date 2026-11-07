
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 25230.3 | 0.135569 | 814.82ms | 213963 | 2560 | 307747 | 8087.52 | 0.0774031 | 0.0978206 | 1(Win) | true |
| Glaze | 3878.68 | 0.0405993 | 5266.31ms | 213963 | 4890 | 2.23077e+06 | 52608.4 | 0.0573892 | 0.638003 | 2(Loss) | true |
