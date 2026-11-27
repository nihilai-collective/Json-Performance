
----
### Instruments Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 712.064 | 0.16095 | 1070.74ms | 7932 | 2560 | 748426 | 10623.4 | 0.0752488 | 1(Win) | true |
| simdjson (ondemand) | 336.238 | 0.225192 | 2244.82ms | 7932 | 640 | 1.6427e+06 | 22497.6 | 0.149127 | 2(Loss) | true |
