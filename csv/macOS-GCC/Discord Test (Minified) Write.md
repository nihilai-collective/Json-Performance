
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11813.8 | 0.390788 | 526.638ms | 56369 | 1280 | 404755 | 4550.4 | 0.123218 | 1(Win) | true |
| simdjson (reflection) | 9095.74 | 0.27805 | 603.722ms | 56369 | 2560 | 691336 | 5910.2 | 0.0270792 | 2(Loss) | true |
| Glaze | 2943.11 | 0.285472 | 2220.46ms | 56369 | 80 | 217513 | 18265.6 | 0.210674 | 3(Loss) | true |
