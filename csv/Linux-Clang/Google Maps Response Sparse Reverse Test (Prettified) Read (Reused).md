
----
### Google Maps Response Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3307.5 | 0.122608 | 1466.32ms | 25388 | 160 | 12888.9 | 7320.31 | 0.0439895 | 1.56439 | 7.20372 | 1.28053 | 0.00303145 | 1.18166e-05 | 3.44651e-06 | 1(Win) | true |
| simdjson (ondemand) | 3163.16 | 0.0404912 | 1496.62ms | 25388 | 2560 | 24591 | 7654.33 | 0.0207203 | 1.6247 | 7.34926 | 1.1342 | 0.00317087 | 9.75485e-06 | 1.93866e-06 | 2(Loss) | true |
