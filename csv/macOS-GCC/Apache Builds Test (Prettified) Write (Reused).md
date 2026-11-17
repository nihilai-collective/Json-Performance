
----
### Apache Builds Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 12524.8 | 0.215934 | 1040.23ms | 136037 | 4890 | 2.44639e+06 | 10358.3 | 0.805729 | 1(Win) | true |
| Glaze | 4578.13 | 0.312607 | 2894.82ms | 136076 | 2560 | 2.01013e+07 | 28346.1 | 2.41161 | 2(Loss) | true |
| simdjson (reflection) | 313.701 | 0.669285 | 5151.43ms | 136037 | 320 | 2.45164e+09 | 413563 | 0.0836363 | 3(Loss) | true |
