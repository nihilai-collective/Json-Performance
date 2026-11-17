
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 848.602 | 0.408628 | 207.302ms | 1811 | 2560 | 177062 | 2035.23 | 0.203034 | 2.87824 | 1(Win) | true |
| Glaze | 393.866 | 0.130393 | 451.002ms | 1811 | 40 | 1307.69 | 4385 | 0.0380228 | 6.24045 | 2(Loss) | true |
| Jsonifier (two-stage) | 338.068 | 0.111175 | 524.442ms | 1811 | 80 | 2580.7 | 5108.75 | 0.0244618 | 7.28667 | 3(Loss) | true |
| simdjson (ondemand) | 134.196 | 0.0843855 | 1304.16ms | 1811 | 40 | 4717.95 | 12870 | 0.0518269 | 18.4329 | 4(Loss) | true |
