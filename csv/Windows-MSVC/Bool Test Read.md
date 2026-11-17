
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 809.924 | 0.12677 | 109.323ms | 905 | 2560 | 4671.75 | 1065.62 | 0.390079 | 3.68893 | 1(Win) | true |
| simdjson (stage-1) | 264.13 | 0.07777 | 329.74ms | 905 | 2560 | 16532 | 3267.62 | 0.0442118 | 11.4243 | 2(Loss) | true |
