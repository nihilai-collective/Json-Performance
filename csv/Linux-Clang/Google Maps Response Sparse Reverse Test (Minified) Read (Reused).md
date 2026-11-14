
----
### Google Maps Response Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1840.6 | 0.0721219 | 1339.01ms | 11812 | 640 | 12469.4 | 6120.2 | 0.0552424 | 2.81566 | 13.836 | 2.59719 | 0.00737042 | 2.14295e-05 | 4.62983e-06 | 1(Win) | true |
| simdjson (ondemand) | 1615.14 | 0.0270027 | 1425.13ms | 11812 | 2560 | 9079.88 | 6974.49 | 0.0426849 | 3.20633 | 14.4206 | 2.36692 | 0.00725719 | 1.51792e-05 | 1.02518e-06 | 2(Loss) | true |
