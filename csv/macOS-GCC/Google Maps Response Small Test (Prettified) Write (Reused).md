
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 21252 | 2.71741 | 56.5929ms | 11521 | 1280 | 252640 | 517 | 0.0386997 | 1(Win) | true |
| Glaze | 3042.89 | 0.615077 | 366.508ms | 11521 | 640 | 315679 | 3610.8 | 0.389235 | 2(Loss) | true |
| simdjson (reflection) | 311.643 | 0.669453 | 3560.93ms | 11521 | 160 | 8.91304e+06 | 35256 | 0.823656 | 3(Loss) | true |
