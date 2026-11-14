
----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4966.03 | 0.0171677 | 5848.96ms | 264040 | 4890 | 370556 | 50706.1 | 0.062061 | 1.02695 | 5.23966 | 0.847497 | 0.00163716 | 3.0918e-06 | 9.65801e-07 | 1(Win) | true |
| simdjson (ondemand) | 4001.93 | 0.0733453 | 7095.15ms | 264040 | 640 | 1.3631e+06 | 62921.7 | 0.31556 | 1.26165 | 6.29984 | 0.918912 | 0.00248464 | 3.21329e-06 | 1.65103e-06 | 2(Loss) | true |
