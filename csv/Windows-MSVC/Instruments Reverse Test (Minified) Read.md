
----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 480.3 | 0.0683415 | 5484.06ms | 108313 | 640 | 1.38256e+07 | 215064 | 0.00247026 | 6.32738 | 1(Win) | true |
| simdjson (ondemand) | 186.994 | 0.143134 | 7004.32ms | 108313 | 640 | 4.00101e+08 | 552400 | 0.376309 | 16.2533 | 2(Loss) | true |
