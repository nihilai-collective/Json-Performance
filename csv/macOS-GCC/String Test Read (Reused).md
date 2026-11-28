
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1706.1 | 0.445859 | 350.629ms | 4215 | 2560 | 282503 | 2356.1 | 1.44315 | 1(Win) | true |
| simdjson (reflection) | 804.076 | 1.1164 | 640.402ms | 4215 | 320 | 996753 | 4999.2 | 1.21477 | 2(Loss) | true |
| Glaze | 766.716 | 0.74309 | 611.519ms | 4215 | 2560 | 3.88552e+06 | 5242.8 | 0.440562 | 3(Loss) | true |
| simdjson (ondemand) | 648.136 | 0.351686 | 719.655ms | 4215 | 1280 | 608952 | 6202 | 0.951833 | 4(Loss) | true |
