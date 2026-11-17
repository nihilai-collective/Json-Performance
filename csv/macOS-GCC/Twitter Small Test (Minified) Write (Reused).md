
----
### Twitter Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 11038 | 2.79692 | 27.807ms | 2963 | 4890 | 250696 | 256 | 3.7232 | 1(Win) | true |
| simdjson (reflection) | 9060.94 | 2.31113 | 36.4449ms | 2963 | 4890 | 254023 | 311.859 | 0.308557 | 2(Loss) | true |
| Glaze | 3003.55 | 1.01298 | 93.6602ms | 2963 | 1280 | 116253 | 940.8 | 0.341297 | 3(Loss) | true |
