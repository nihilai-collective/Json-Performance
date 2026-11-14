
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1739.3 | 0.735165 | 176.635ms | 2821 | 4890 | 632321 | 1546.78 | 3.01076 | 1(Win) | true |
| simdjson (ondemand) | 1314.66 | 1.11244 | 218.414ms | 2821 | 1280 | 663351 | 2046.4 | 0.078125 | 2(Loss) | true |
