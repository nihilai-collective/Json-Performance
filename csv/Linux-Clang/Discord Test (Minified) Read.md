
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21793.6 | 0.0419048 | 252.79ms | 56369 | 40 | 42.7378 | 2466.68 | 0.0415367 | 0.112335 | 1(Win) | true |
| simdjson (stage-1) | 18776.2 | 0.0512502 | 292.654ms | 56369 | 40 | 86.1224 | 2863.07 | 0.00378395 | 0.130577 | 2(Loss) | true |
