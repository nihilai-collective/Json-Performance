
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 319.509 | 0.29781 | 541.248ms | 1811 | 30 | 7774.47 | 5405.5 | 0.104722 | 1(Win) | true |
| simdjson (ondemand) | 196.973 | 0.193516 | 920.82ms | 1811 | 2560 | 737054 | 8768.24 | 2.03519 | 2(Loss) | true |
