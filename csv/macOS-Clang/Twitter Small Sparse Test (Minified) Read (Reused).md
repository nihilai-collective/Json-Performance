
----
### Twitter Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4035.9 | 0.0453322 | 72.0818ms | 2821 | 1280 | 116.882 | 666.595 | 0.0971359 | 1(Win) | true |
| simdjson (ondemand) | 3670.56 | 0.0853881 | 79.4438ms | 2821 | 1280 | 501.357 | 732.945 | 0.0807542 | 2(Loss) | true |
