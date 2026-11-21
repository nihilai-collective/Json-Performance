
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 17200.8 | 0.358252 | 613.8ms | 108313 | 320 | 148112 | 6005.26 | 0.0723327 | 0.14329 | 1(Win) | true |
| Glaze | 3897.13 | 0.11144 | 2694.54ms | 108313 | 4890 | 4.26643e+06 | 26505.5 | 0.343564 | 0.634679 | 2(Loss) | true |
