
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 866.997 | 0.136462 | 1292.84ms | 11579 | 2560 | 773341 | 12736.6 | 0.13113 | 3.49995 | 1(Win) | true |
| Jsonifier (generic) | 845.947 | 0.0483798 | 1320.78ms | 11579 | 4890 | 195026 | 13053.5 | 0.0617362 | 3.58674 | 2(Loss) | true |
