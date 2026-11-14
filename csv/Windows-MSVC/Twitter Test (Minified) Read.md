
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 919.679 | 0.920938 | 6992.65ms | 264040 | 80 | 5.08649e+08 | 273800 | 0.892668 | 2.69141 | 1(Win) | true |
| simdjson (ondemand) | 798.393 | 0.588946 | 8395.92ms | 264040 | 160 | 5.52048e+08 | 315394 | 0.0736631 | 3.10053 | 2(Loss) | true |
