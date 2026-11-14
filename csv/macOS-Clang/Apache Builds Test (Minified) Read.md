
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6963.24 | 0.188516 | 1324.05ms | 94653 | 4890 | 2.92046e+06 | 12963.5 | 1.1377 | 1(Win) | true |
| simdjson (stage-1) | 6674.99 | 0.196159 | 1327.09ms | 94653 | 4890 | 3.44107e+06 | 13523.3 | 0.294664 | 2(Loss) | true |
