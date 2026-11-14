
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7385.91 | 0.263527 | 1216.03ms | 94653 | 4890 | 5.07249e+06 | 12221.7 | 1.38258 | 1(Win) | true |
| simdjson (stage-1) | 5781.67 | 0.800102 | 1555.05ms | 94653 | 320 | 4.99346e+06 | 15612.8 | 0.0102491 | 2(Loss) | true |
