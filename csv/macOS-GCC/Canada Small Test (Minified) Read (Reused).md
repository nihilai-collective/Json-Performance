
----
### Canada Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 912.598 | 0.641871 | 600.646ms | 4630 | 160 | 154319 | 4838.4 | 0.19802 | 1(Win) | true |
| Jsonifier (two-stage) | 729.692 | 0.43392 | 745.713ms | 4630 | 80 | 55156 | 6051.2 | 0.473684 | 2(Loss) | true |
| simdjson (reflection) | 688.74 | 0.329936 | 750.27ms | 4630 | 1280 | 572691 | 6411 | 0.334919 | 3(Loss) | true |
| Glaze | 611.027 | 0.10535 | 833.778ms | 4630 | 4890 | 283414 | 7226.37 | 0.122012 | 4(Loss) | true |
| simdjson (ondemand) | 540.401 | 0.123 | 928.443ms | 4630 | 2560 | 258570 | 8170.8 | 0.390711 | 5(Loss) | true |
