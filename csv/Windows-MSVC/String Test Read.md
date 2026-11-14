
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5110.09 | 0.296265 | 190.154ms | 9578 | 40 | 1121.79 | 1787.5 | 0.0466418 | 0.472669 | 1(Win) | true |
| simdjson (stage-1) | 1354.48 | 0.0827628 | 687.784ms | 9578 | 80 | 2492.09 | 6743.75 | 0.0185391 | 1.814 | 2(Loss) | true |
