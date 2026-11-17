
----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1775.85 | 0.0488726 | 1363.53ms | 11812 | 1280 | 12302 | 6343.34 | 0.284297 | 2.91473 | 13.836 | 2.59719 | 0.00774517 | 1.11116e-05 | 1.12439e-06 | 1(Win) | true |
| simdjson (ondemand) | 1594.04 | 0.0327217 | 1443.05ms | 11812 | 4890 | 26147.4 | 7066.81 | 0.222613 | 3.22607 | 14.4312 | 2.37216 | 0.00689893 | 2.32684e-05 | 6.71737e-06 | 2(Loss) | true |
