
----
### Random Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12378.7 | 0.193578 | 3636.25ms | 461466 | 80 | 378906 | 35552 | 0.018005 | 1(Win) | true |
| simdjson (reflection) | 8776.29 | 0.0867685 | 4987.94ms | 461466 | 4890 | 9.25744e+06 | 50145.1 | 0.0375301 | 2(Loss) | true |
| Glaze | 2286.78 | 0.523653 | 9248.82ms | 461466 | 640 | 6.49978e+08 | 192449 | 0.190647 | 3(Loss) | true |
