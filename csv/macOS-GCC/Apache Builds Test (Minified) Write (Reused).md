
----
### Apache Builds Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 13257.6 | 0.27312 | 690.045ms | 94653 | 640 | 221324 | 6808.8 | 0.140795 | 1(Win) | true |
| simdjson (reflection) | 10556.1 | 0.143919 | 859.524ms | 94653 | 2560 | 387740 | 8551.3 | 0.0198761 | 2(Loss) | true |
| Glaze | 5842.41 | 0.230637 | 1472.44ms | 94653 | 2560 | 3.25076e+06 | 15450.5 | 0.204751 | 3(Loss) | true |
