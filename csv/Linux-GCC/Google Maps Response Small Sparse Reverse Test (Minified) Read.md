
----
### Google Maps Response Small Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1871.54 | 0.122857 | 945.115ms | 4390 | 1280 | 9668.11 | 2237 | 0.260655 | 2.74682 | 13.061 | 2.45786 | 0.00399541 | 3.89735e-05 | 1.33471e-05 | 1(Win) | true |
| simdjson (ondemand) | 1621.83 | 0.0418201 | 985.301ms | 4390 | 2560 | 2983.52 | 2581.43 | 0.0637924 | 3.19876 | 13.8995 | 2.40797 | 0.00470494 | 2.09104e-05 | 1.01438e-05 | 2(Loss) | true |
