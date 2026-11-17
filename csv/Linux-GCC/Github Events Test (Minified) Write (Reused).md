
----
### Github Events Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14270.4 | 0.214843 | 393.459ms | 58581 | 30 | 2122.3 | 3914.9 | 0.00170292 | 0.172277 | 1(Win) | true |
| simdjson (reflection) | 10997.5 | 0.245243 | 507.513ms | 58581 | 2560 | 397336 | 5079.98 | 0.0283739 | 0.223936 | 2(Loss) | true |
| Glaze | 7744.28 | 0.105174 | 733.798ms | 58581 | 4890 | 281500 | 7213.99 | 0.354264 | 0.318518 | 3(Loss) | true |
