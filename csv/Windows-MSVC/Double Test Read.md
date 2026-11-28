
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 833.579 | 0.395508 | 209.659ms | 1811 | 2560 | 171907 | 2071.91 | 0.118635 | 2.93269 | 1(Win) | true |
| Glaze | 414.92 | 0.130854 | 403.002ms | 1811 | 80 | 2373.42 | 4162.5 | 0.180505 | 5.92442 | 2(Loss) | true |
| simdjson (ondemand) | 310.63 | 0.184952 | 551.446ms | 1811 | 30 | 3172.41 | 5560 | 0.120048 | 7.92965 | 3(Loss) | true |
