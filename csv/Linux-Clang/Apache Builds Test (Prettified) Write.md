
----
### Apache Builds Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19484.6 | 0.0461554 | 667.267ms | 136037 | 30 | 283.333 | 6658.33 | 0.335293 | 0.126568 | 1(Win) | true |
| Glaze | 6251.84 | 0.138188 | 2082.91ms | 136076 | 2560 | 2.10634e+06 | 20757.4 | 0.194542 | 0.395489 | 2(Loss) | true |
