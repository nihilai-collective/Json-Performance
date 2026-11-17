
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1620.79 | 0.0527973 | 3629.2ms | 56369 | 4890 | 1.49954e+06 | 33167.6 | 0.177194 | 1.52623 | 1(Win) | true |
| simdjson (ondemand) | 1401.48 | 0.0581239 | 4189.29ms | 56369 | 4890 | 2.43066e+06 | 38357.8 | 0.151102 | 1.76517 | 2(Loss) | true |
