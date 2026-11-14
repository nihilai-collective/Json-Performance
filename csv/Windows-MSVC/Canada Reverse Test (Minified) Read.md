
----
### Canada Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 387.121 | 0.371551 | 7715.63ms | 2090234 | 80 | 2.92836e+10 | 5.1493e+06 | 0.260013 | 7.85065 | 1(Win) | true |
| simdjson (ondemand) | 374.014 | 0.378896 | 7989.69ms | 2090234 | 80 | 3.26245e+10 | 5.32975e+06 | 0.0563899 | 8.12595 | 2(Loss) | true |
