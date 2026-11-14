
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1805.89 | 0.503086 | 6020.16ms | 108313 | 30 | 2.48419e+06 | 57199.1 | 0.383437 | 1.37027 | 1(Win) | true |
| simdjson (ondemand) | 1602.54 | 0.0447121 | 6630.74ms | 108313 | 4890 | 4.06164e+06 | 64457.2 | 0.394584 | 1.54419 | 2(Loss) | true |
