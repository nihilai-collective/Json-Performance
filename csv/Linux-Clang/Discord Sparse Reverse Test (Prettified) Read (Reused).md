
----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2824.85 | 0.101606 | 3914.17ms | 83958 | 40 | 33176.8 | 28344.3 | 0.023074 | 1.8254 | 8.34173 | 1.5007 | 0.00373252 | 5.65759e-06 | 3.57322e-06 | 1(Win) | true |
| simdjson (ondemand) | 2196.98 | 0.0274827 | 4654.2ms | 83958 | 4890 | 490571 | 36444.9 | 0.0219479 | 2.31861 | 10.9546 | 1.7133 | 0.00483646 | 2.16999e-05 | 1.58688e-05 | 2(Loss) | true |
