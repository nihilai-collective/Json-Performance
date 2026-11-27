
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 794.948 | 0.624126 | 231.75ms | 1811 | 2560 | 470700 | 2172.6 | 0.676602 | 1(Win) | true |
| Glaze | 775.569 | 0.314449 | 231.443ms | 1811 | 4890 | 239775 | 2226.89 | 0.604739 | 2(Loss) | true |
| simdjson (reflection) | 268.415 | 0.16983 | 682.804ms | 1811 | 4890 | 583932 | 6434.45 | 4.38589 | 3(Loss) | true |
| simdjson (ondemand) | 247.217 | 1.21411 | 666.548ms | 1811 | 1280 | 9.20883e+06 | 6986.2 | 2.70458 | 4(Loss) | true |
