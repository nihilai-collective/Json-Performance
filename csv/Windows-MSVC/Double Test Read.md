
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 471.886 | 0.158244 | 357.263ms | 1811 | 80 | 2683.54 | 3660 | 0.480439 | 6.39671 | 1(Win) | true |
| simdjson (ondemand) | 266.657 | 0.303824 | 674.693ms | 1811 | 320 | 123915 | 6476.88 | 0.0289575 | 11.3595 | 2(Loss) | true |
