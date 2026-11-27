
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1775.86 | 0.303526 | 69.0067ms | 1213 | 640 | 2501.93 | 651.406 | 0.216346 | 1.33107 | 1(Win) | true |
| simdjson (stage-1) | 733.026 | 0.222421 | 162.642ms | 1213 | 160 | 1971.31 | 1578.12 | 0.0395883 | 3.31424 | 2(Loss) | true |
