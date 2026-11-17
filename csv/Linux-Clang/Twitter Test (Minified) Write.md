
----
### Twitter Test (Minified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17510 | 0.460083 | 2653.24ms | 475954 | 320 | 4.55176e+06 | 25922.6 | 0.202573 | 0.141209 | 1(Win) | true |
| Glaze | 5467.08 | 0.165909 | 8425.87ms | 475954 | 640 | 1.21434e+07 | 83025.2 | 0.645716 | 0.452667 | 2(Loss) | true |
