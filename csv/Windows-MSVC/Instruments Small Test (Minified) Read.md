
----
### Instruments Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2189.41 | 0.199252 | 223.48ms | 4669 | 160 | 2627.36 | 2033.75 | 0.184729 | 1.38103 | 1(Win) | true |
| Jsonifier (two-stage) | 1446.27 | 0.16027 | 318.711ms | 4669 | 80 | 1947.78 | 3078.75 | 0.203417 | 2.08903 | 2(Loss) | true |
| Glaze | 1311.07 | 0.147424 | 352.582ms | 4669 | 160 | 4011.01 | 3396.25 | 0.0367918 | 2.30309 | 3(Loss) | true |
| simdjson (ondemand) | 897.061 | 0.352305 | 504.284ms | 4669 | 4890 | 1.49538e+06 | 4963.66 | 0.847375 | 3.37416 | 4(Loss) | true |
