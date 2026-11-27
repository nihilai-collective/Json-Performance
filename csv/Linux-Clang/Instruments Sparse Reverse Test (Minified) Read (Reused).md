
----
### Instruments Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3562.34 | 0.0379314 | 3642.96ms | 108313 | 1280 | 154845 | 28996.5 | 0.186511 | 1.44357 | 7.80531 | 1.40025 | 0.00129581 | 1.27308e-05 | 9.1171e-06 | 1(Win) | true |
| simdjson (ondemand) | 2582.85 | 0.169479 | 4711.22ms | 108313 | 80 | 367522 | 39992.7 | 0.0487201 | 1.95898 | 10.1484 | 1.54533 | 0.00315013 | 4.61625e-06 | 2.65434e-06 | 2(Loss) | true |
