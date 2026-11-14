
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 532.216 | 0.235302 | 730.475ms | 3873 | 30 | 8000 | 6940 | 0 | 4.63586 | 1(Win) | true |
| simdjson (ondemand) | 286.012 | 0.339366 | 1310.51ms | 3873 | 320 | 614629 | 12914.1 | 0.378477 | 8.63876 | 2(Loss) | true |
