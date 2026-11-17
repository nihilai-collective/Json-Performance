
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1311.97 | 0.0380384 | 136.265ms | 1811 | 160 | 40.1191 | 1316.42 | 0.0137703 | 1.85024 | 1(Win) | true |
| simdjson (stage-1) | 659.549 | 0.0279503 | 266.478ms | 1811 | 160 | 85.7105 | 2618.61 | 0.0458048 | 3.71513 | 2(Loss) | true |
