
----
### Github Events Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 18789.5 | 0.112582 | 404.307ms | 78778 | 30 | 607.909 | 3998.43 | 0.0208458 | 0.130882 | 1(Win) | true |
| Glaze | 6095.17 | 0.268452 | 1234.35ms | 78778 | 320 | 350364 | 12325.9 | 0.337776 | 0.405308 | 2(Loss) | true |
| simdjson (reflection) | 657.079 | 0.725059 | 5863.39ms | 78778 | 30 | 2.06178e+07 | 114337 | 0.00239065 | 3.76674 | 3(Loss) | true |
