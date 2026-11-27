
----
### Discord Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1810.36 | 0.0396374 | 3717.35ms | 56369 | 1280 | 177327 | 29694.5 | 0.10638 | 2.81628 | 13.0874 | 2.50778 | 0.00623065 | 9.86801e-06 | 3.74208e-06 | 1(Win) | true |
| simdjson (ondemand) | 1350.19 | 0.0748552 | 4748.88ms | 56369 | 640 | 568476 | 39814.7 | 0.0877046 | 3.76842 | 17.4557 | 2.89404 | 0.00732863 | 3.26254e-05 | 2.17872e-05 | 2(Loss) | true |
