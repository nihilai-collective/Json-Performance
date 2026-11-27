
----
### Discord Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 725.554 | 0.0685224 | 1362.1ms | 4857 | 640 | 12247.4 | 6384.08 | 0.0590929 | 7.14765 | 29.875 | 5.87523 | 0.00679657 | 4.66466e-05 | 1.73718e-05 | 1(Win) | true |
| simdjson (ondemand) | 224.986 | 0.0241128 | 2793.17ms | 4857 | 4890 | 120512 | 20587.9 | 0.0180871 | 22.9095 | 107.434 | 22.5987 | 0.0480666 | 0.000223572 | 0.000124375 | 2(Loss) | true |
