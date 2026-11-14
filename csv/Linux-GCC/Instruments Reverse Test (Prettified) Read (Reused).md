
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 950.937 | 0.124959 | 9928.66ms | 183677 | 40 | 2.11935e+06 | 184206 | 0.0350979 | 5.41278 | 23.5742 | 4.7191 | 0.00632578 | 0.000163058 | 0.000153803 | 1(Win) | true |
| simdjson (ondemand) | 443.125 | 0.0852473 | 5142.98ms | 183677 | 640 | 7.26773e+07 | 395302 | 0.0791326 | 11.5249 | 52.9936 | 10.6925 | 0.0462122 | 4.37249e-05 | 2.78512e-05 | 2(Loss) | true |
