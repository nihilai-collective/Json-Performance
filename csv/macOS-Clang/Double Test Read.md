
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 910.62 | 0.184755 | 213.306ms | 1811 | 160 | 1964.6 | 1896.62 | 0.789818 | 1(Win) | true |
| Jsonifier (two-stage) | 853.771 | 0.0852826 | 209.097ms | 1811 | 160 | 476.206 | 2022.91 | 0.0777975 | 2(Loss) | true |
| Glaze | 744.169 | 0.224668 | 253.28ms | 1811 | 40 | 1087.52 | 2320.85 | 0.175632 | 3(Loss) | true |
| simdjson (ondemand) | 277.597 | 0.2733 | 610.061ms | 1811 | 640 | 185040 | 6221.62 | 0.198058 | 4(Loss) | true |
