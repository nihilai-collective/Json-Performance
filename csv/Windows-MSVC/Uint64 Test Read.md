
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 856.696 | 0.212435 | 141.257ms | 1213 | 320 | 2633.13 | 1350.31 | 0.253924 | 2.83904 | 1(Win) | true |
| Glaze | 337.262 | 0.248094 | 387.269ms | 1213 | 30 | 2172.41 | 3430 | 0.193986 | 7.23842 | 2(Loss) | true |
| simdjson (ondemand) | 267.625 | 0.0766141 | 446.506ms | 1213 | 160 | 1754.72 | 4322.5 | 0.403226 | 9.19083 | 3(Loss) | true |
