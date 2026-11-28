
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1473.62 | 0.0605137 | 121.2ms | 1811 | 80 | 40.2403 | 1172.01 | 0.107605 | 1.64446 | 1(Win) | true |
| Glaze | 1027.26 | 0.064946 | 167.423ms | 1811 | 40 | 47.6917 | 1681.28 | 0.0945807 | 2.37025 | 2(Loss) | true |
| simdjson (ondemand) | 416.798 | 0.149159 | 426.476ms | 1811 | 2560 | 97796.7 | 4143.74 | 0.172403 | 5.90322 | 3(Loss) | true |
| simdjson (reflection) | 392.514 | 0.413295 | 440.617ms | 1811 | 4890 | 1.61717e+06 | 4400.1 | 0.269293 | 6.27083 | 4(Loss) | true |
