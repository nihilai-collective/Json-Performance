
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3183.59 | 0.0558444 | 1484.91ms | 25388 | 40 | 721.512 | 7605.23 | 0.187785 | 1.62713 | 7.30054 | 1.30365 | 0.00313337 | 7.87774e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3165.02 | 0.0226278 | 1484.74ms | 25388 | 2560 | 7670.57 | 7649.84 | 0.00503458 | 1.63555 | 7.43434 | 1.15444 | 0.00355611 | 5.63135e-06 | 7.6931e-07 | 2(Loss) | true |
