
----
### Discord Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15496.6 | 0.0688152 | 349.188ms | 56369 | 40 | 227.949 | 3469 | 0.119293 | 0.15848 | 1(Win) | true |
| Glaze | 4158.07 | 0.0719851 | 1299.88ms | 56369 | 4890 | 423536 | 12928.5 | 0.00807431 | 0.59419 | 2(Loss) | true |
