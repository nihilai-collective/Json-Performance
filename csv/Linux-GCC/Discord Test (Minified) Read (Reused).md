
----
### Discord Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1866.13 | 0.137684 | 3262.7ms | 56369 | 1280 | 2.01362e+06 | 28807.1 | 0.0348859 | 1.32551 | 1(Win) | true |
| simdjson (ondemand) | 1699.95 | 0.120721 | 3500.56ms | 56369 | 1280 | 1.86545e+06 | 31623.2 | 0.056092 | 1.45522 | 2(Loss) | true |
