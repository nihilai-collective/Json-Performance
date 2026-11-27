
----
### Github Events Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14519.5 | 0.0908154 | 15.8399ms | 1996 | 1280 | 18.1445 | 131.102 | 0.171329 | 0.134163 | 1(Win) | true |
| simdjson (reflection) | 12500.8 | 0.127921 | 17.9313ms | 1996 | 640 | 24.2835 | 152.273 | 0.0605041 | 0.163839 | 2(Loss) | true |
| Glaze | 6674.42 | 0.0743372 | 31.4225ms | 1996 | 640 | 28.7665 | 285.198 | 0.0279489 | 0.336168 | 3(Loss) | true |
