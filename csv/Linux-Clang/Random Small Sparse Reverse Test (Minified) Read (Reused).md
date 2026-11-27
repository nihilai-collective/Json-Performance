
----
### Random Small Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2058.95 | 0.0965118 | 964.789ms | 4926 | 1280 | 6206.79 | 2281.65 | 0.0515245 | 2.53702 | 11.1955 | 2.0745 | 0.00421885 | 1.45909e-05 | 3.17194e-07 | 1(Win) | true |
| simdjson (ondemand) | 1580.59 | 0.0613362 | 1032.28ms | 4926 | 2560 | 8507.94 | 2972.18 | 0.291494 | 3.26208 | 13.9724 | 2.28583 | 0.00735764 | 5.53504e-05 | 2.80717e-05 | 2(Loss) | true |
