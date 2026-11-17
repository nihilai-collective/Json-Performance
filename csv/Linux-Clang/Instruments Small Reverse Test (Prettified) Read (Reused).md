
----
### Instruments Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 939.934 | 0.0180422 | 1529.36ms | 7932 | 4890 | 10310 | 8047.95 | 0.0244478 | 5.50458 | 24.0252 | 4.73512 | 0.004907 | 2.6194e-05 | 3.4805e-06 | 1(Win) | true |
| simdjson (ondemand) | 418.042 | 0.0378088 | 2565.51ms | 7932 | 2560 | 119826 | 18095.2 | 0.330761 | 12.2572 | 60.8433 | 10.9129 | 0.0220792 | 2.79229e-05 | 5.46639e-06 | 2(Loss) | true |
