
----
### Google Maps Response Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4295.8 | 0.0279011 | 1300.29ms | 25388 | 4890 | 12092.6 | 5636.18 | 0.0790753 | 1.19999 | 5.58551 | 0.909564 | 0.0018222 | 7.7408e-06 | 2.10234e-06 | 1(Win) | true |
| simdjson (ondemand) | 4016.23 | 0.0651761 | 1367.07ms | 25388 | 640 | 9880.45 | 6028.51 | 0.181551 | 1.28725 | 5.88569 | 0.865921 | 0.00189041 | 7.75465e-06 | 2.3387e-06 | 2(Loss) | true |
