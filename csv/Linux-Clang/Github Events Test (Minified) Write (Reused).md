
----
### Github Events Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16682.9 | 0.176143 | 338.095ms | 58581 | 2560 | 89072.9 | 3348.78 | 0.0503545 | 0.147258 | 1(Win) | true |
| Glaze | 6792.82 | 0.0983261 | 836.454ms | 58581 | 40 | 2615.84 | 8224.45 | 0.134536 | 0.363339 | 2(Loss) | true |
