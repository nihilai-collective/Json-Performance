
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1671.3 | 0.252075 | 235.284ms | 3873 | 30 | 931.034 | 2210 | 0 | 1.80083 | 1(Win) | true |
| Glaze | 1000.21 | 0.110772 | 374.882ms | 3873 | 1280 | 21418.2 | 3692.81 | 0.0676533 | 3.02202 | 2(Loss) | true |
| Jsonifier (two-stage) | 913.581 | 0.116087 | 415.874ms | 3873 | 640 | 14097.6 | 4042.97 | 0.0270458 | 3.31018 | 3(Loss) | true |
| simdjson (ondemand) | 560.27 | 0.0843655 | 668.674ms | 3873 | 80 | 2474.68 | 6592.5 | 0.0757863 | 5.41057 | 4(Loss) | true |
