
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1780.45 | 0.134396 | 6081.47ms | 108313 | 640 | 3.89094e+06 | 58016.5 | 0.144392 | 1.38992 | 1(Win) | true |
| simdjson (ondemand) | 1592.72 | 0.0664341 | 6585.54ms | 108313 | 2560 | 4.75232e+06 | 64854.8 | 0.345344 | 1.55373 | 2(Loss) | true |
