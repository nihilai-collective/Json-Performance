
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 941.219 | 0.17106 | 5687.52ms | 108313 | 1280 | 4.51117e+07 | 109746 | 0.0532906 | 2.62972 | 1(Win) | true |
| simdjson (ondemand) | 813.814 | 0.282358 | 6609.31ms | 108313 | 320 | 4.11019e+07 | 126928 | 0.169181 | 3.04169 | 2(Loss) | true |
