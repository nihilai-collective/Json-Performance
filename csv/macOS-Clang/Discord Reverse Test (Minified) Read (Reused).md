
----
### Discord Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 693.353 | 0.172754 | 8256.72ms | 56369 | 160 | 2.87044e+06 | 77532.9 | 0.100019 | 1(Win) | true |
| simdjson (ondemand) | 147.494 | 0.0950306 | 9594.94ms | 56369 | 1280 | 1.53556e+08 | 364473 | 0.251805 | 2(Loss) | true |
