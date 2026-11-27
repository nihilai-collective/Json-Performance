
----
### Discord Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3238.76 | 0.0700766 | 3524ms | 83958 | 2560 | 768336 | 24722 | 0.188161 | 1.5797 | 8.15817 | 1.46156 | 0.0020998 | 6.0298e-06 | 1.99598e-06 | 1(Win) | true |
| simdjson (ondemand) | 2199.81 | 0.0179029 | 4665.07ms | 83958 | 4890 | 207639 | 36398 | 0.230877 | 2.31767 | 10.4535 | 1.76438 | 0.00669623 | 1.298e-05 | 7.57025e-06 | 2(Loss) | true |
