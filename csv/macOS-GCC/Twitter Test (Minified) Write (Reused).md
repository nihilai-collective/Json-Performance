
----
### Twitter Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 15576 | 0.866361 | 3149.42ms | 475954 | 30 | 1.91222e+06 | 29141.3 | 0.668994 | 1(Win) | true |
| simdjson (reflection) | 11697.6 | 0.216358 | 4119.72ms | 475954 | 40 | 281931 | 38803.2 | 0.43245 | 2(Loss) | true |
| Glaze | 4037.84 | 0.605064 | 5960.86ms | 475954 | 80 | 3.70104e+07 | 112413 | 0.638859 | 3(Loss) | true |
