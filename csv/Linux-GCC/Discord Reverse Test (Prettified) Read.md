
----
### Discord Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 889.682 | 0.0340836 | 9768.17ms | 83958 | 1280 | 1.20436e+06 | 89996.8 | 0.0836733 | 5.76106 | 24.757 | 5.24701 | 0.00840141 | 1.48977e-05 | 7.01616e-06 | 1(Win) | true |
| simdjson (ondemand) | 313.413 | 0.191368 | 6709.77ms | 83958 | 40 | 9.56069e+06 | 255473 | 0.114363 | 16.3006 | 89.3577 | 18.9219 | 0.025466 | 5.15139e-05 | 3.03723e-05 | 2(Loss) | true |
