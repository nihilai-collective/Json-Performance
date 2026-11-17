
----
### Random Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 10137.8 | 4.14291 | 53.131ms | 5094 | 640 | 252246 | 479.2 | 0.498339 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 10081 | 1.50795 | 51.9959ms | 5094 | 4890 | 258222 | 481.898 | 0.290895 | 1(Tie) | true |
| Glaze | 2262.28 | 0.625714 | 229.387ms | 5094 | 1280 | 231094 | 2147.4 | 0.913621 | 3(Loss) | true |
