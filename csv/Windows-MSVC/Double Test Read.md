
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 705.751 | 0.34017 | 247.526ms | 1811 | 2560 | 177405 | 2447.19 | 0.0159597 | 3.46621 | 1(Win) | true |
| Glaze | 382.844 | 0.104283 | 432.356ms | 1811 | 80 | 1770.57 | 4511.25 | 0.138351 | 6.42831 | 2(Loss) | true |
| simdjson (ondemand) | 303.533 | 0.122668 | 589.292ms | 1811 | 40 | 1948.72 | 5690 | 0.530035 | 8.11509 | 3(Loss) | true |
