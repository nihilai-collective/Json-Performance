
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1341.68 | 0.110801 | 132.336ms | 1811 | 30 | 61.0299 | 1287.27 | 0.103471 | 1.80885 | 1(Win) | true |
| simdjson (stage-1) | 617.705 | 0.0531876 | 284.842ms | 1811 | 40 | 88.4615 | 2796 | 0.0620318 | 3.96922 | 2(Loss) | true |
