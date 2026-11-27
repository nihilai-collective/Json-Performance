
----
### Twitter Small Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7195.56 | 0.154167 | 777.285ms | 3770 | 160 | 94.942 | 499.663 | 0.0200095 | 0.774799 | 3.07109 | 0.388064 | 0.000508952 | 1.49204e-05 | 1.65782e-06 | 1(Win) | true |
| simdjson (ondemand) | 6762.46 | 0.0375344 | 774.933ms | 3770 | 4890 | 194.733 | 531.663 | 0.150642 | 0.81359 | 3.26631 | 0.339788 | 0.000496439 | 1.30185e-05 | 2.06126e-06 | 2(Loss) | true |
