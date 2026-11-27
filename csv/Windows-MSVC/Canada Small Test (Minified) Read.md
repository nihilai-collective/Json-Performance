
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 183.234 | 0.0871903 | 2459.89ms | 4630 | 4890 | 2.15872e+06 | 24097.7 | 0.310776 | 13.4964 | 1(Win) | true |
| Jsonifier (generic) | 178.137 | 0.155571 | 2465.98ms | 4630 | 2560 | 3.80673e+06 | 24787.1 | 0.17555 | 13.8821 | 2(Loss) | true |
