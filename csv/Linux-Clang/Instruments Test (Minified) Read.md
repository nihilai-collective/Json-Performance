
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1519.74 | 0.01545 | 7524.57ms | 108313 | 4890 | 539250 | 67969 | 0.0816415 | 3.37926 | 14.863 | 3.01435 | 0.00431072 | 7.94675e-06 | 3.66279e-06 | 1(Win) | true |
| simdjson (ondemand) | 1439.23 | 0.0253859 | 7916.31ms | 108313 | 2560 | 849818 | 71771.1 | 0.161921 | 3.53711 | 16.6368 | 2.50869 | 0.00605099 | 9.5102e-06 | 4.89395e-06 | 2(Loss) | true |
