
----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2910.9 | 0.0346428 | 3735.37ms | 83958 | 2560 | 232453 | 27506.5 | 0.279488 | 1.76101 | 8.65416 | 1.50905 | 0.00261584 | 4.46652e-06 | 1.11663e-06 | 1(Win) | true |
| simdjson (ondemand) | 2205.4 | 0.0470023 | 4667.26ms | 83958 | 1280 | 372733 | 36305.7 | 0.0808792 | 2.33714 | 10.9993 | 1.72752 | 0.00561146 | 4.19667e-06 | 8.00251e-07 | 2(Loss) | true |
