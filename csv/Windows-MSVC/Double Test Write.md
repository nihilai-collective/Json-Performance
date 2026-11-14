
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 348.814 | 0.100009 | 497.773ms | 1811 | 2560 | 62772.7 | 4951.37 | 0.0953687 | 8.682 | 1(Win) | true |
| Glaze | 160.051 | 0.587224 | 1075.87ms | 1798 | 1280 | 5.06619e+06 | 10713.5 | 0.00802077 | 18.9462 | 2(Loss) | true |
