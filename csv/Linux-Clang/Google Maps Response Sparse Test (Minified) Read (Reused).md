
----
### Google Maps Response Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2418.51 | 0.0267244 | 1194.87ms | 11812 | 4890 | 7576.6 | 4657.74 | 0.116446 | 2.1448 | 10.3452 | 1.89604 | 0.00281534 | 1.34521e-05 | 1.09071e-06 | 1(Win) | true |
| simdjson (ondemand) | 2033.37 | 0.0233663 | 1281.92ms | 11812 | 4890 | 8194.09 | 5539.96 | 0.0717774 | 2.54943 | 11.5132 | 1.82797 | 0.00364047 | 1.22575e-05 | 1.41965e-06 | 2(Loss) | true |
