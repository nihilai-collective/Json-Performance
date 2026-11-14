
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3027.53 | 0.129703 | 126.599ms | 3873 | 640 | 1602.5 | 1220 | 0.306435 | 0.79968 | 1(Win) | true |
| simdjson (stage-1) | 623.126 | 0.120623 | 594.911ms | 3873 | 40 | 2044.87 | 5927.5 | 0.210438 | 3.94597 | 2(Loss) | true |
