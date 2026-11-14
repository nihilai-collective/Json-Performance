
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1686.14 | 0.26625 | 8609.41ms | 264040 | 1280 | 2.02368e+08 | 149340 | 0.127033 | 1(Win) | true |
| simdjson (ondemand) | 1440.6 | 0.254064 | 9715.9ms | 264040 | 640 | 1.26217e+08 | 174794 | 0.0932495 | 2(Loss) | true |
