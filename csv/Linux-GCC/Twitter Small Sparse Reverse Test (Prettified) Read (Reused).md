
----
### Twitter Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4960.6 | 0.0603279 | 787.444ms | 3770 | 1280 | 244.715 | 724.781 | 0.0844369 | 1.09478 | 4.51353 | 0.665517 | 0.000807982 | 1.94794e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4419.66 | 0.0656873 | 798.277ms | 3770 | 320 | 91.373 | 813.491 | 0.0318944 | 1.22377 | 4.99655 | 0.687798 | 0.000565318 | 2.15517e-05 | 0 | 2(Loss) | true |
