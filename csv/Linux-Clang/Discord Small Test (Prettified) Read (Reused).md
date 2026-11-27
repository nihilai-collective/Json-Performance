
----
### Discord Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2458.01 | 0.0352603 | 1047.85ms | 6701 | 4890 | 4109.53 | 2599.89 | 0.0819858 | 2.11823 | 8.81107 | 1.51022 | 0.00157526 | 4.58681e-05 | 1.48316e-05 | 1(Win) | true |
| simdjson (ondemand) | 2179.42 | 0.0836864 | 1043.78ms | 6701 | 2560 | 15415.1 | 2932.23 | 0.041733 | 2.3694 | 9.82883 | 1.5235 | 0.000861637 | 3.00795e-05 | 1.0318e-05 | 2(Loss) | true |
