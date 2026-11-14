
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 643.249 | 0.0683084 | 6361.47ms | 83958 | 1280 | 9.2539e+06 | 124475 | 0.125119 | 4.72407 | 1(Win) | true |
| simdjson (ondemand) | 252.2 | 0.0898073 | 8107.12ms | 83958 | 1280 | 1.04056e+08 | 317480 | 0.000344511 | 12.0505 | 2(Loss) | true |
