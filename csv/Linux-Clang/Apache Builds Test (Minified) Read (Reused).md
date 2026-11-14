
----
### Apache Builds Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2238.13 | 0.0864825 | 6053.77ms | 94653 | 80 | 97329.2 | 40331.9 | 0.0903638 | 2.30237 | 11.1446 | 2.08843 | 0.00621428 | 4.62215e-06 | 1.45267e-06 | 1(Win) | true |
| simdjson (ondemand) | 1712 | 0.0178572 | 7237.99ms | 94653 | 4890 | 433512 | 52726.8 | 0.10129 | 2.98838 | 12.7232 | 2.22457 | 0.00855281 | 5.55252e-06 | 1.1602e-06 | 2(Loss) | true |
