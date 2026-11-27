
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 798.353 | 0.518984 | 217.832ms | 1811 | 30 | 3781.61 | 2163.33 | 0 | 3.06368 | 1(Win) | true |
| Glaze | 393.418 | 0.167427 | 427.416ms | 1811 | 30 | 1620.69 | 4390 | 0.0759878 | 6.24082 | 2(Loss) | true |
| simdjson (ondemand) | 292.122 | 0.475829 | 594.065ms | 1811 | 1280 | 1.01302e+06 | 5912.27 | 0.250371 | 8.43208 | 3(Loss) | true |
