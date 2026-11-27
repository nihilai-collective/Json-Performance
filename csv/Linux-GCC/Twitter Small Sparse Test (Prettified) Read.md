
----
### Twitter Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6950.44 | 0.0835899 | 765.42ms | 3770 | 640 | 119.659 | 517.284 | 0.0217529 | 0.794894 | 3.16764 | 0.377719 | 0.00050688 | 4.97347e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 6279.89 | 0.0710866 | 771.963ms | 3770 | 4890 | 809.958 | 572.518 | 0.112231 | 0.875359 | 3.46048 | 0.354908 | 0.000417189 | 1.43204e-05 | 3.52584e-06 | 2(Loss) | true |
