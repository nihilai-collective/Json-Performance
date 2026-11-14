
----
### Canada Small Test (Minified) Write Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2083.78 | 0.357617 | 209.041ms | 4630 | 4890 | 280803 | 2118.99 | 4.07097 | 1(Win) | true |
| Glaze | 1657.75 | 0.281676 | 269.736ms | 4630 | 4890 | 275253 | 2663.55 | 0.606298 | 2(Loss) | true |
| simdjson (reflection) | 910.922 | 0.200417 | 494.96ms | 4630 | 2560 | 241607 | 4847.3 | 0.0556701 | 3(Loss) | true |
