
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1726.53 | 0.0911587 | 846.015ms | 2158 | 640 | 755.668 | 1192 | 0.196747 | 3.08448 | 11.0765 | 2.07507 | 0.000469184 | 5.21316e-05 | 2.17215e-06 | 1(Win) | true |
| simdjson (ondemand) | 1692.55 | 0.0295785 | 848.433ms | 2158 | 4890 | 632.529 | 1215.93 | 0.0288312 | 3.14859 | 12.1492 | 1.98378 | 0.000593502 | 6.43442e-05 | 6.91771e-06 | 2(Loss) | true |
