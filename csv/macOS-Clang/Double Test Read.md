
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 868.033 | 0.194566 | 196.827ms | 1811 | 40 | 599.456 | 1989.67 | 0.101672 | 1(Win) | true |
| Glaze | 784.232 | 0.0545152 | 214.898ms | 1811 | 640 | 922.493 | 2202.29 | 0.127404 | 2(Loss) | true |
| simdjson (ondemand) | 303.604 | 0.0988002 | 626.006ms | 1811 | 2560 | 80868.1 | 5688.67 | 0.0680166 | 3(Loss) | true |
