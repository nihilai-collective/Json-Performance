
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 842.233 | 0.198129 | 218.488ms | 1811 | 160 | 2641.12 | 2050.62 | 0.152625 | 2.89953 | 1(Win) | true |
| Glaze | 415.919 | 0.135302 | 401.531ms | 1811 | 80 | 2525.32 | 4152.5 | 0.362538 | 5.91649 | 2(Loss) | true |
| simdjson (ondemand) | 310.351 | 0.137244 | 573.417ms | 1811 | 40 | 2333.33 | 5565 | 0.447227 | 7.94568 | 3(Loss) | true |
