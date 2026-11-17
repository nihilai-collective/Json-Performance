
----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1041.8 | 0.0667463 | 1066ms | 3770 | 160 | 848.956 | 3451.08 | 0.130746 | 5.003 | 20.4496 | 3.81379 | 0.00124668 | 5.13926e-05 | 9.94695e-06 | 1(Win) | true |
| simdjson (ondemand) | 469.773 | 0.0397064 | 1488.39ms | 3770 | 2560 | 23641.1 | 7653.38 | 0.0260387 | 11.0182 | 49.722 | 8.51326 | 0.0118975 | 5.09781e-05 | 1.23301e-05 | 2(Loss) | true |
