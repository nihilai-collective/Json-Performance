
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3721.35 | 0.117833 | 95.7507ms | 3370 | 30 | 31.0678 | 863.633 | 0.0385817 | 0.64545 | 1(Win) | true |
| Jsonifier (two-stage) | 3194.63 | 0.10349 | 110.136ms | 3370 | 40 | 43.3583 | 1006.02 | 0.0802847 | 0.754332 | 2(Loss) | true |
| Glaze | 2684.03 | 0.310014 | 128.313ms | 3370 | 4890 | 67384.1 | 1197.41 | 0.0911753 | 0.902553 | 3(Loss) | true |
| simdjson (ondemand) | 2080.84 | 0.363669 | 163.44ms | 3370 | 2560 | 80767.6 | 1544.52 | 0.0414693 | 1.16689 | 4(Loss) | true |
