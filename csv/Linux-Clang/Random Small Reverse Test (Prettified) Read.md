
----
### Random Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1204.2 | 0.0457414 | 1370.75ms | 8150 | 160 | 1394.63 | 6454.46 | 0.0157812 | 4.3054 | 17.6831 | 3.52528 | 0.00627607 | 6.21166e-05 | 3.60429e-05 | 1(Win) | true |
| simdjson (ondemand) | 756.729 | 0.0634686 | 1750.49ms | 8150 | 320 | 13598.9 | 10271.1 | 0.0326051 | 6.83219 | 30.0207 | 5.40552 | 0.0150947 | 2.45399e-05 | 2.30061e-06 | 2(Loss) | true |
