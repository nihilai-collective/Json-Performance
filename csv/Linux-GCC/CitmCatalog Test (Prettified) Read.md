
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 14910.3 | 0.0729144 | 8152.79ms | 1151920 | 40 | 115440 | 73677.5 | 0.328507 | 0.339071 | 1.80099 | 0.0980694 | 0.000173037 | 0.000881029 | 4.4925e-06 | 1(Win) | true |
| simdjson (stage-1) | 14122.6 | 0.0388793 | 8692.6ms | 1151920 | 160 | 146343 | 77787.1 | 0.0262025 | 0.364735 | 1.9361 | 0.073131 | 0.000389035 | 0.00500692 | 6.59768e-06 | 2(Loss) | true |
