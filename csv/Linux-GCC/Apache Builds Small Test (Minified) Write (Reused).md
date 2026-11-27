
----
### Apache Builds Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 12484.8 | 0.599716 | 24.4193ms | 2632 | 40 | 58.1513 | 201.05 | 0.0248756 | 0.172084 | 1(Win) | true |
| simdjson (reflection) | 10042.5 | 0.117132 | 27.181ms | 2632 | 160 | 13.7138 | 249.944 | 0.0725689 | 0.22097 | 2(Loss) | true |
| Glaze | 4686.9 | 0.149491 | 57.5411ms | 2632 | 40 | 25.6385 | 535.55 | 0.0528771 | 0.500085 | 3(Loss) | true |
