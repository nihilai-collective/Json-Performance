
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 442.672 | 0.177087 | 910.288ms | 4215 | 4890 | 1.26449e+06 | 9080.61 | 0.257138 | 5.56897 | 1(Win) | true |
| simdjson (ondemand) | 397.916 | 0.186257 | 1070.19ms | 4215 | 4890 | 1.73121e+06 | 10102 | 1.32071 | 6.19722 | 2(Loss) | true |
