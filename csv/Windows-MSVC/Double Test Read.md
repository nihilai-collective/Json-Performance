
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 535.419 | 0.33266 | 326.05ms | 1811 | 2560 | 294775 | 3225.7 | 0.130615 | 4.58249 | 1(Win) | true |
| simdjson (ondemand) | 326.691 | 0.149941 | 597.556ms | 1811 | 30 | 1885.06 | 5286.67 | 0.126263 | 7.54057 | 2(Loss) | true |
