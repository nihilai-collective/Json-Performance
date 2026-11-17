
----
### Twitter Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1335.64 | 0.265341 | 6723.67ms | 360584 | 80 | 3.73367e+07 | 257465 | 0.0543468 | 1.8534 | 1(Win) | true |
| simdjson (ondemand) | 1142.44 | 0.135026 | 7807.07ms | 360584 | 1280 | 2.11443e+08 | 301004 | 0.271782 | 2.16681 | 2(Loss) | true |
