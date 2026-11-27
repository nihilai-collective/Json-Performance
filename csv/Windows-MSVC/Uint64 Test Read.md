
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 2093.77 | 1.01691 | 60.6784ms | 1213 | 80 | 2525.32 | 552.5 | 0 | 1.40377 | 1(Win) | true |
| simdjson (stage-1) | 887.576 | 0.255754 | 147.417ms | 1213 | 30 | 333.333 | 1303.33 | 0.761421 | 3.38098 | 2(Loss) | true |
