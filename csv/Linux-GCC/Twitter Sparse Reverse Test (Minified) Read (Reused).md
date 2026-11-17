
----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4829.93 | 0.197987 | 6035.95ms | 264040 | 40 | 426180 | 52135 | 0.0677547 | 1.05994 | 5.24586 | 0.856045 | 0.00214664 | 2.08302e-06 | 1.42024e-06 | 1(Win) | true |
| simdjson (ondemand) | 3998.47 | 0.0625059 | 7097.44ms | 264040 | 320 | 495841 | 62976.1 | 0.00178642 | 1.26918 | 6.26582 | 0.935804 | 0.00245659 | 1.01784e-06 | 5.91766e-08 | 2(Loss) | true |
