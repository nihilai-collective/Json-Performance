
----
### Double Test Write Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 450.941 | 0.191593 | 387.51ms | 1811 | 40 | 2153.85 | 3830 | 0 | 5.43361 | 1(Win) | true |
| Glaze | 132.112 | 0.290653 | 1306.32ms | 1798 | 4890 | 6.95911e+06 | 12979.2 | 0.379099 | 18.6926 | 2(Loss) | true |
