
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1030.17 | 0.322837 | 191.004ms | 1811 | 80 | 2343.57 | 1676.53 | 0.648899 | 1(Win) | true |
| simdjson (stage-1) | 612.064 | 0.324344 | 290.314ms | 1811 | 1280 | 107218 | 2821.77 | 1.05623 | 2(Loss) | true |
