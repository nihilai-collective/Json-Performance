
----
### Twitter Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1873.68 | 0.0789546 | 7632.86ms | 264040 | 1280 | 1.44117e+07 | 134392 | 0.0727021 | 1(Win) | true |
| simdjson (ondemand) | 1597.68 | 0.0599386 | 8800.9ms | 264040 | 2560 | 2.28461e+07 | 157609 | 0.0190735 | 2(Loss) | true |
