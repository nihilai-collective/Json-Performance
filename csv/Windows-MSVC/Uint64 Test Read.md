
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 828.675 | 0.328212 | 141.919ms | 1213 | 4890 | 102653 | 1395.97 | 0.142541 | 2.93007 | 1(Win) | true |
| Glaze | 337.507 | 0.326635 | 342.539ms | 1213 | 1280 | 160432 | 3427.5 | 0.0364564 | 7.22382 | 2(Loss) | true |
| simdjson (ondemand) | 274.45 | 0.0953112 | 429.525ms | 1213 | 80 | 1291.14 | 4215 | 0.118765 | 8.96245 | 3(Loss) | true |
