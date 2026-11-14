
----
### Random Test (Minified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11451.3 | 0.215939 | 3922.91ms | 461466 | 640 | 4.40768e+06 | 38431.2 | 0.116436 | 1(Win) | true |
| simdjson (reflection) | 7909.31 | 0.210669 | 5827ms | 461466 | 1280 | 1.75878e+07 | 55641.8 | 0.357084 | 2(Loss) | true |
| Glaze | 2170.82 | 0.0888463 | 5218.31ms | 461466 | 1280 | 4.15261e+07 | 202729 | 0.255647 | 3(Loss) | true |
