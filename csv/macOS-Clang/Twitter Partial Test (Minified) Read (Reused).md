
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 4718.65 | 1.77662 | 5104.03ms | 466906 | 30 | 8.43209e+07 | 94365.3 | 0.176202 | 1(Win) | true |
| Jsonifier (two-stage) | 4388.54 | 0.49688 | 5076.71ms | 466906 | 640 | 1.62668e+08 | 101463 | 0.0145825 | 2(Loss) | true |
| simdjson (ondemand) | 4161.75 | 0.15635 | 5624.74ms | 466906 | 640 | 1.79094e+07 | 106992 | 0.152442 | 3(Loss) | true |
| Glaze | 2012.58 | 0.321583 | 5595.5ms | 466906 | 640 | 3.23978e+08 | 221246 | 1.75491 | 4(Loss) | true |
