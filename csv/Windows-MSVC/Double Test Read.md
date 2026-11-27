
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 762.098 | 0.440121 | 245.357ms | 1811 | 320 | 31835.4 | 2266.25 | 0.0551876 | 3.95152 | 1(Win) | true |
| Glaze | 451.826 | 0.238585 | 394.897ms | 1811 | 40 | 3326.92 | 3822.5 | 0.503944 | 6.69651 | 2(Loss) | true |
| simdjson (ondemand) | 330.23 | 0.227348 | 560.745ms | 1811 | 30 | 4241.38 | 5230 | 0.0637755 | 9.1605 | 3(Loss) | true |
