
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2356.49 | 0.476096 | 161.844ms | 3873 | 4890 | 272310 | 1567.41 | 0.437589 | 1(Win) | true |
| Glaze | 1438.53 | 0.905407 | 257.419ms | 3873 | 640 | 345878 | 2567.6 | 0.10917 | 2(Loss) | true |
| Jsonifier (two-stage) | 829.049 | 0.839134 | 453.543ms | 3873 | 320 | 447247 | 4455.2 | 0.836895 | 3(Loss) | true |
| simdjson (ondemand) | 413.041 | 0.349193 | 906.018ms | 3873 | 1280 | 1.2481e+06 | 8942.4 | 0.943694 | 4(Loss) | true |
