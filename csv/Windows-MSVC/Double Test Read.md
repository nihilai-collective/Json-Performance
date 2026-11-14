
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 945.69 | 0.109254 | 186.432ms | 1811 | 2560 | 10191.8 | 1826.29 | 0.440801 | 3.17987 | 1(Win) | true |
| Jsonifier (two-stage) | 544.256 | 0.299654 | 314.115ms | 1811 | 30 | 2712.64 | 3173.33 | 0.527983 | 5.53648 | 2(Loss) | true |
| Glaze | 460.101 | 0.431602 | 346.782ms | 1811 | 80 | 20998.4 | 3753.75 | 0.166778 | 6.57744 | 3(Loss) | true |
| simdjson (ondemand) | 260.651 | 0.0565724 | 662.877ms | 1811 | 4890 | 68712.5 | 6626.11 | 0.152052 | 11.6246 | 4(Loss) | true |
