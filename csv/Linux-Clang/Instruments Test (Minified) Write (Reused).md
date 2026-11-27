
----
### Instruments Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16849.2 | 0.0287004 | 620.686ms | 108313 | 30 | 92.8747 | 6130.57 | 0.147567 | 0.146338 | 1(Win) | true |
| Glaze | 4129.73 | 0.0571414 | 2562.22ms | 108313 | 4890 | 998915 | 25012.6 | 0.030774 | 0.59889 | 2(Loss) | true |
