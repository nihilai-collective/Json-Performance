
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1810.05 | 0.561656 | 445.165ms | 7932 | 320 | 176310 | 4179.2 | 0.114987 | 1(Win) | true |
| simdjson (ondemand) | 1608.11 | 1.12641 | 531.851ms | 7932 | 80 | 224606 | 4704 | 0 | 2(Loss) | true |
