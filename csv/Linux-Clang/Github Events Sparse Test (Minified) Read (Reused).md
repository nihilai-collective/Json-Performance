
----
### Github Events Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8918.49 | 0.0345856 | 1318.06ms | 53331 | 4890 | 19022.9 | 5702.8 | 0.0574477 | 0.578793 | 2.71585 | 0.380286 | 0.000726358 | 3.99557e-06 | 1.2884e-06 | 1(Win) | true |
| simdjson (ondemand) | 7281.78 | 0.0463238 | 1448.9ms | 53331 | 4890 | 51191.9 | 6984.61 | 0.0346865 | 0.706603 | 3.18573 | 0.380267 | 0.000817666 | 1.01116e-05 | 5.99336e-06 | 2(Loss) | true |
