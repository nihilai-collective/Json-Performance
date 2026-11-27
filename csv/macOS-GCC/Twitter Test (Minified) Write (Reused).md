
----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14977.8 | 0.171166 | 3329.05ms | 475954 | 640 | 1.72206e+06 | 30305.2 | 0.0171617 | 1(Win) | true |
| simdjson (reflection) | 12236.8 | 0.149039 | 3698.29ms | 475954 | 2560 | 7.82415e+06 | 37093.5 | 0.0773122 | 2(Loss) | true |
| Glaze | 4527.68 | 0.157194 | 5255.63ms | 475954 | 160 | 3.97346e+06 | 100251 | 0.103632 | 3(Loss) | true |
