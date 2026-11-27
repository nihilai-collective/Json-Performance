
----
### Instruments Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14377.5 | 2.96282 | 33.2649ms | 4669 | 2560 | 215543 | 309.7 | 0.0969619 | 1(Win) | true |
| simdjson (reflection) | 9629.08 | 1.60855 | 49.1978ms | 4669 | 4890 | 270557 | 462.423 | 0.703693 | 2(Loss) | true |
| Glaze | 2258.34 | 0.191107 | 200.979ms | 4669 | 4890 | 69427.2 | 1971.67 | 0.232381 | 3(Loss) | true |
