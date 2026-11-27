
----
### Discord Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12724.4 | 0.236165 | 38.7175ms | 4857 | 40 | 29.5635 | 364.025 | 0.0571978 | 0.179957 | 1(Win) | true |
| simdjson (reflection) | 9428.52 | 0.229668 | 51.8535ms | 4857 | 40 | 50.9224 | 491.275 | 0.282476 | 0.248888 | 2(Loss) | true |
| Glaze | 4626.91 | 0.276639 | 106.052ms | 4857 | 30 | 230.093 | 1001.1 | 0.0266445 | 0.521007 | 3(Loss) | true |
