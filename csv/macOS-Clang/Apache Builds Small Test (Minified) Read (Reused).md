
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1645.49 | 0.0395122 | 181.15ms | 2632 | 1280 | 464.999 | 1525.42 | 0.151108 | 1(Win) | true |
| simdjson (ondemand) | 1315.34 | 0.0334198 | 218.777ms | 2632 | 1280 | 520.611 | 1908.3 | 0.0191633 | 2(Loss) | true |
