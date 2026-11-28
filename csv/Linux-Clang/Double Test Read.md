
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1314.94 | 0.0755942 | 135.045ms | 1811 | 40 | 39.4333 | 1313.45 | 0.041892 | 1.84335 | 1(Win) | true |
| Glaze | 778.861 | 0.572109 | 212.807ms | 1811 | 80 | 12875.5 | 2217.47 | 0.408699 | 3.13798 | 2(Loss) | true |
| simdjson (ondemand) | 421.238 | 0.268018 | 411.62ms | 1811 | 1280 | 154568 | 4100.07 | 0.615609 | 5.83826 | 3(Loss) | true |
