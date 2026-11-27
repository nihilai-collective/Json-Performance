
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2114.26 | 0.198345 | 194.886ms | 4215 | 80 | 1137.66 | 1901.25 | 0.065703 | 1.14949 | 1(Win) | true |
| simdjson (stage-1) | 1330.49 | 0.152337 | 316.216ms | 4215 | 80 | 1694.62 | 3021.25 | 0.206441 | 1.83719 | 2(Loss) | true |
