
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1289.5 | 0.155082 | 6299.25ms | 83958 | 1280 | 1.18689e+07 | 62092.5 | 0.152222 | 1.919 | 1(Win) | true |
| simdjson (ondemand) | 1121.04 | 0.085172 | 7219.01ms | 83958 | 2560 | 9.47364e+06 | 71423.6 | 0.0775468 | 2.20762 | 2(Loss) | true |
