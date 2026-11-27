
----
### Discord Small Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4216.88 | 0.0463555 | 876.028ms | 6701 | 4890 | 2413.29 | 1515.48 | 0.057712 | 1.25327 | 5.41307 | 0.895687 | 0.000941043 | 2.05994e-05 | 7.35476e-06 | 1(Win) | true |
| simdjson (ondemand) | 3025.25 | 0.0679909 | 934.922ms | 6701 | 4890 | 10087.2 | 2112.41 | 0.448704 | 1.7224 | 7.61812 | 1.10879 | 0.00221845 | 1.23291e-05 | 3.78419e-06 | 2(Loss) | true |
