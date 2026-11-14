
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 941.762 | 0.0755207 | 1531.52ms | 7932 | 320 | 11775.1 | 8032.33 | 0.0251265 | 5.4973 | 24.0252 | 4.73512 | 0.00479663 | 2.04866e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 423.653 | 0.0629815 | 2514.83ms | 7932 | 640 | 80937.7 | 17855.5 | 0.0416361 | 12.1764 | 60.8362 | 10.9115 | 0.0239436 | 2.56083e-05 | 1.37891e-06 | 2(Loss) | true |
