
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1760.33 | 0.0324035 | 958.229ms | 4390 | 4890 | 2904.26 | 2378.33 | 0.0246889 | 2.97246 | 13.7934 | 2.57517 | 0.00377708 | 3.07447e-05 | 6.19553e-06 | 1(Win) | true |
| simdjson (ondemand) | 1623.53 | 0.0505547 | 980.682ms | 4390 | 160 | 271.927 | 2578.72 | 0.0230197 | 3.22188 | 14.3966 | 2.3533 | 0.00278616 | 2.2779e-05 | 0 | 2(Loss) | true |
