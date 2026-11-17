
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1138.39 | 0.66098 | 5420.42ms | 4197496 | 80 | 4.32178e+10 | 3.5164e+06 | 0.272753 | 2.66975 | 1(Win) | true |
| simdjson (ondemand) | 966.797 | 0.673726 | 6397.52ms | 4197496 | 80 | 6.2254e+10 | 4.14052e+06 | 0.365491 | 3.1436 | 2(Loss) | true |
