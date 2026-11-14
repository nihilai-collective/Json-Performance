
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 803.311 | 0.117819 | 5641.81ms | 183677 | 320 | 2.11214e+07 | 218058 | 0.042402 | 3.78315 | 1(Win) | true |
| simdjson (ondemand) | 329.721 | 0.129685 | 6781.3ms | 183677 | 640 | 3.03792e+08 | 531261 | 0.255165 | 9.21755 | 2(Loss) | true |
