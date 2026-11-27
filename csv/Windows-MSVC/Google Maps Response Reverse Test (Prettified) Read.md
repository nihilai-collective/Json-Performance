
----
### Google Maps Response Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1022.8 | 0.111133 | 2374.92ms | 25388 | 2560 | 1.77177e+06 | 23672.3 | 0.0895175 | 2.96875 | 1(Win) | true |
| simdjson (ondemand) | 909.238 | 0.146087 | 2680.61ms | 25388 | 2560 | 3.87406e+06 | 26628.8 | 0.229195 | 3.33967 | 2(Loss) | true |
