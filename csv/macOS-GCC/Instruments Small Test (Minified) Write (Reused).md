
----
### Instruments Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14345.1 | 2.95755 | 33.4441ms | 4669 | 2560 | 215749 | 310.4 | 0.844704 | 1(Win) | true |
| simdjson (reflection) | 7814.51 | 2.44634 | 61.7052ms | 4669 | 1280 | 248706 | 569.8 | 0.869868 | 2(Loss) | true |
| Glaze | 2056.12 | 0.278553 | 217.144ms | 4669 | 4890 | 177941 | 2165.58 | 0.874884 | 3(Loss) | true |
