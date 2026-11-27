
----
### Twitter Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5079.98 | 0.0491901 | 5708.6ms | 264040 | 1280 | 760995 | 49568.8 | 0.102747 | 0.994428 | 5.17444 | 0.871853 | 0.00175063 | 4.58027e-06 | 2.78722e-06 | 1(Win) | true |
| simdjson (ondemand) | 3892.92 | 0.0576318 | 7257.28ms | 264040 | 640 | 889390 | 64683.6 | 0.00920502 | 1.30127 | 6.37663 | 0.935427 | 0.00185045 | 2.21557e-05 | 1.43918e-05 | 2(Loss) | true |
