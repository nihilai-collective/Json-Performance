
----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 10990.9 | 0.632661 | 902.814ms | 94653 | 1280 | 3.45585e+06 | 8213 | 1.31001 | 1(Win) | true |
| simdjson (reflection) | 7970.3 | 0.234193 | 1166.75ms | 94653 | 4890 | 3.44014e+06 | 11325.6 | 1.83692 | 2(Loss) | true |
| Glaze | 4085.44 | 0.323057 | 2195.37ms | 94653 | 4890 | 2.49149e+07 | 22095.1 | 1.23712 | 3(Loss) | true |
