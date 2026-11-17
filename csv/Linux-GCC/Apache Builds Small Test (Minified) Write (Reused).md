
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16299.3 | 0.124764 | 17.7913ms | 2632 | 640 | 23.626 | 153.998 | 0.135127 | 0.126412 | 1(Win) | true |
| simdjson (reflection) | 10596.3 | 0.470098 | 26.2125ms | 2632 | 4890 | 6063.91 | 236.883 | 0.124078 | 0.208638 | 2(Loss) | true |
| Glaze | 4914 | 0.138998 | 54.5331ms | 2632 | 40 | 20.1641 | 510.8 | 0.287958 | 0.476871 | 3(Loss) | true |
