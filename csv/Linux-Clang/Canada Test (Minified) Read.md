
----
### Canada Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 782.974 | 0.0442233 | 7955.7ms | 2090234 | 160 | 2.02823e+08 | 2.54594e+06 | 1.23497 | 3.16199 | 1(Win) | true |
| simdjson (ondemand) | 717.715 | 0.0374137 | 8770.13ms | 2090234 | 40 | 4.31925e+07 | 2.77743e+06 | 0.992382 | 3.44952 | 2(Loss) | true |
