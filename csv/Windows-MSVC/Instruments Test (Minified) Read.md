
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1020.13 | 0.108166 | 5168.05ms | 108313 | 640 | 7.67733e+06 | 101257 | 0.0483226 | 2.97867 | 1(Win) | true |
| simdjson (ondemand) | 897.458 | 0.048317 | 5873.39ms | 108313 | 2560 | 7.91721e+06 | 115098 | 0.0274827 | 3.38586 | 2(Loss) | true |
