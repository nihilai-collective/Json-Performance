
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2531.58 | 0.0770117 | 118.088ms | 2889 | 160 | 112.395 | 1088.32 | 0.280037 | 0.953647 | 1(Win) | true |
| Jsonifier (two-stage) | 2253.44 | 0.246464 | 130.779ms | 2889 | 4890 | 44403.6 | 1222.65 | 0.0066497 | 1.0757 | 2(Loss) | true |
| Glaze | 2126.56 | 0.0445258 | 136.631ms | 2889 | 320 | 106.492 | 1295.6 | 0.146435 | 1.13994 | 3(Loss) | true |
| simdjson (reflection) | 2079 | 0.133637 | 144.729ms | 2889 | 80 | 250.918 | 1325.24 | 0.326476 | 1.16657 | 4(Loss) | true |
| simdjson (ondemand) | 1194.94 | 0.07499 | 242.722ms | 2889 | 160 | 478.329 | 2305.69 | 0.0260294 | 2.04793 | 5(Loss) | true |
