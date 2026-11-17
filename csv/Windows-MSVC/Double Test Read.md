
----
### Double Test Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1548.7 | 0.117764 | 114.162ms | 1811 | 2560 | 4415.36 | 1115.2 | 0.28453 | 1.92563 | 1(Win) | true |
| simdjson (stage-1) | 523.191 | 0.0913232 | 333.233ms | 1811 | 1280 | 11632.9 | 3301.09 | 0.00473306 | 5.76775 | 2(Loss) | true |
