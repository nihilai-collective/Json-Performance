
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1409.28 | 0.107622 | 4045.38ms | 56369 | 1280 | 2.15722e+06 | 38145.5 | 0.0831494 | 1(Win) | true |
| simdjson (ondemand) | 1116.04 | 0.332439 | 5211.01ms | 56369 | 80 | 2.05133e+06 | 48168.2 | 0.221233 | 2(Loss) | true |
