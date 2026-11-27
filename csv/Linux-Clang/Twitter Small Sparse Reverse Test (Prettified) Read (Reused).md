
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5438.23 | 0.195341 | 794.435ms | 3770 | 80 | 133.427 | 661.125 | 0.105992 | 1.0053 | 4.38223 | 0.665782 | 0.000809019 | 0 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4638.04 | 0.135049 | 799.435ms | 3770 | 1280 | 1402.84 | 775.188 | 0.0406316 | 1.15647 | 4.96472 | 0.679841 | 0.000756797 | 1.1812e-05 | 4.35179e-06 | 2(Loss) | true |
