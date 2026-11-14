
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1184.83 | 0.580211 | 149.95ms | 1811 | 4890 | 349789 | 1457.68 | 1.70819 | 1(Win) | true |
| simdjson (stage-1) | 554.839 | 0.778177 | 308.587ms | 1811 | 1280 | 751050 | 3112.8 | 1.66793 | 2(Loss) | true |
