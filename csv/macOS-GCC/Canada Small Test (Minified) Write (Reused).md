
----
### Canada Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2386.42 | 0.318988 | 187.028ms | 4630 | 4890 | 170344 | 1850.27 | 0.453678 | 1(Win) | true |
| simdjson (reflection) | 2143.45 | 0.61715 | 209.564ms | 4630 | 640 | 103442 | 2060 | 0.232468 | 2(Loss) | true |
| Glaze | 1986.7 | 0.288295 | 225.654ms | 4630 | 4890 | 200762 | 2222.54 | 0.272533 | 3(Loss) | true |
