
----
### Discord Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2730.09 | 0.0486269 | 3682.11ms | 83958 | 4890 | 994561 | 29328.2 | 0.0748548 | 1.8774 | 9.24078 | 1.69763 | 0.00280979 | 5.96632e-05 | 4.3412e-05 | 1(Win) | true |
| simdjson (ondemand) | 1964 | 0.0641102 | 4821.97ms | 83958 | 1280 | 874393 | 40768.1 | 0.0377106 | 2.59352 | 11.4716 | 1.98512 | 0.00702656 | 1.93828e-05 | 9.82634e-06 | 2(Loss) | true |
