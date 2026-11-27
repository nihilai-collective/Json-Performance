
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 839.928 | 0.0681018 | 1323.79ms | 11579 | 4890 | 391999 | 13147.1 | 0.229646 | 3.61298 | 1(Win) | true |
| simdjson (ondemand) | 832.902 | 0.0942974 | 1332.22ms | 11579 | 1280 | 200062 | 13258 | 0.0671315 | 3.64347 | 2(Loss) | true |
