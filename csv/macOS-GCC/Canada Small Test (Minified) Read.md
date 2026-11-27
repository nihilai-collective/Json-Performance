
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 487.579 | 0.141605 | 923.065ms | 4630 | 1280 | 210494 | 9056 | 0.229156 | 1(Win) | true |
| simdjson (ondemand) | 478.657 | 0.288023 | 941.884ms | 4630 | 640 | 451803 | 9224.8 | 0.130254 | 2(Loss) | true |
