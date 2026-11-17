
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2432.04 | 0.0837663 | 1046.9ms | 7932 | 640 | 4344.54 | 3110.38 | 0.0170326 | 2.14563 | 9.73298 | 1.37771 | 0.000969175 | 1.61529e-05 | 2.36384e-06 | 1(Win) | true |
| Jsonifier (generic) | 2296.08 | 0.0338176 | 1060.38ms | 7932 | 4890 | 6069.95 | 3294.54 | 0.0347543 | 2.26001 | 9.01488 | 1.70222 | 0.00113212 | 2.68128e-05 | 7.34773e-06 | 2(Loss) | true |
