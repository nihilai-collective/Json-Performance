
----
### Github Events Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6687.73 | 0.0336939 | 1675.86ms | 65103 | 2560 | 25048.8 | 9283.72 | 0.267363 | 0.766411 | 3.67762 | 0.57661 | 0.00130808 | 3.75007e-06 | 1.35002e-06 | 1(Win) | true |
| simdjson (ondemand) | 4966.16 | 0.0457294 | 2013.83ms | 65103 | 1280 | 41837.1 | 12502 | 0.151028 | 1.03759 | 4.94332 | 0.758337 | 0.00194351 | 3.82807e-06 | 1.22402e-06 | 2(Loss) | true |
