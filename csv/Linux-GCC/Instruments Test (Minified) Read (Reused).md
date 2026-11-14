
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1723.18 | 0.208895 | 6243.89ms | 108313 | 160 | 2.50888e+06 | 59944.8 | 0.324965 | 1.43612 | 1(Win) | true |
| Jsonifier (generic) | 1630.45 | 0.105755 | 6505.51ms | 108313 | 1280 | 5.74587e+06 | 63353.8 | 0.493303 | 1.51784 | 2(Loss) | true |
