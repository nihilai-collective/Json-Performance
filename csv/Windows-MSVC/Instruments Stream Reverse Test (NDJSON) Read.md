
----
### Instruments Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 721.222 | 0.0871272 | 8727.89ms | 4197496 | 30 | 7.01569e+08 | 5.55036e+06 | 0.521228 | 3.43276 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 397.029 | 0.228352 | 7570.75ms | 4197496 | 40 | 2.12034e+10 | 1.00825e+07 | 5.0128 | 6.23578 | -(Loss) | false |
