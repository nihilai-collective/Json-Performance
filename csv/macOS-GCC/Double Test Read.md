
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 891.363 | 0.451431 | 197.502ms | 1811 | 2560 | 195863 | 1937.6 | 0.431655 | 1(Win) | true |
| Glaze | 814.979 | 0.631184 | 213.205ms | 1811 | 640 | 114508 | 2119.2 | 1.8063 | 2(Loss) | true |
| simdjson (ondemand) | 281.178 | 0.175921 | 624.753ms | 1811 | 4890 | 570974 | 6142.38 | 0.579288 | 3(Loss) | true |
| simdjson (reflection) | 232.638 | 1.42546 | 694.048ms | 1811 | 80 | 895935 | 7424 | 1.69492 | 4(Loss) | true |
