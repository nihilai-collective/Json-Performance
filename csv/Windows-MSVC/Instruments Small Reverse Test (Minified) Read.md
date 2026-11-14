
----
### Instruments Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 446.135 | 0.139682 | 1002.13ms | 4669 | 320 | 62194 | 9980.62 | 0.0813415 | 6.79814 | 1(Win) | true |
| simdjson (ondemand) | 199.366 | 0.146109 | 2333.17ms | 4669 | 1280 | 1.36304e+06 | 22334.3 | 0.156116 | 15.2309 | 2(Loss) | true |
