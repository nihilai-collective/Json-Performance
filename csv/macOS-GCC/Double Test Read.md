
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1296.64 | 0.655121 | 137.074ms | 1811 | 4890 | 372349 | 1331.99 | 0.516448 | 1(Win) | true |
| simdjson (stage-1) | 602.366 | 1.65369 | 288.04ms | 1811 | 80 | 179851 | 2867.2 | 2.51716 | 2(Loss) | true |
