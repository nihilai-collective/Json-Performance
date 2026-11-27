
----
### Google Maps Response Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10177 | 1.71919 | 43.9652ms | 4390 | 4890 | 244591 | 411.38 | 0.824504 | 1(Win) | true |
| simdjson (reflection) | 9073.2 | 1.56647 | 49.1059ms | 4390 | 4890 | 255484 | 461.428 | 0.201568 | 2(Loss) | true |
| Glaze | 1977.53 | 0.242456 | 214.069ms | 4390 | 4890 | 128843 | 2117.1 | 0.0285516 | 3(Loss) | true |
